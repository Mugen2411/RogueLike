#include "GraphicRenderQueue.h"
#include <algorithm>

namespace mugen_engine
{
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> MEGraphicRenderQueue::m_constantDescHeap = nullptr;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> MEGraphicRenderQueue::m_constantBuffers;
	int MEGraphicRenderQueue::m_maxReserve = 0x1FFF;
	std::deque<MEGraphicRenderQueue::RENDER_DATA> MEGraphicRenderQueue::m_reserveList;
	std::vector<const MEGraphicRenderQueue::RENDER_DATA*> MEGraphicRenderQueue::m_reservePointerList;
	uint32_t MEGraphicRenderQueue::m_descriptorHeapIncrementSize = 0;
	MEGraphicDevice* MEGraphicRenderQueue::m_pDevice = nullptr;
	std::vector<CONSTANT_DATA*> MEGraphicRenderQueue::m_pMapMatrix;

	/**********************************************************************//**
		@brief			初期化
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderQueue::Initialize(MEGraphicDevice& device)
	{
		m_pDevice = &device;
		m_descriptorHeapIncrementSize = device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = m_maxReserve * 2;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		auto result = device.GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_constantDescHeap.ReleaseAndGetAddressOf()));

		if(FAILED(result))
		{
			OutputDebugStringA("DX12 DescriptorHeap Initialize Error.\n");
		}
		_InitalizeConstantBuffer(device);
	}

	/**********************************************************************//**
		@brief			描画を予約する
		@param[in]		vbView				頂点バッファビュー
		@param[in]		constData			定数バッファのデータ
		@param[in]		textureHeap			テクスチャのディスクリプタヒープ
		@param[in]		blendType			ブレンドタイプ
		@param[in]		cmdList				コマンドリスト
		@param[in]		pipeline			パイプライン
		@param[in]		renderTarget		レンダーターゲット
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderQueue::ReserveRender(D3D12_VERTEX_BUFFER_VIEW* vbView, CONSTANT_DATA constData,
		MEGraphicGpuResourceManager* textureHeap, int blendType, float priority, MEGraphicCommandList* cmdList, MEGraphicPipeline* pipeline,
		MEGraphicRenderTarget* renderTarget)
	{
		static RENDER_DATA tmp = {};
		tmp.vertexBufferView = vbView;
		tmp.textureHeap = textureHeap;
		tmp.blendType = blendType;
		tmp.constData = constData;
		tmp.priority = priority;
		tmp.order = m_reserveList.size();

		m_reserveList.push_back(tmp);
	}

	/**********************************************************************//**
		@brief			予約された描画を全部発火する
		@param[in]		cmdList				コマンドリスト
		@param[in]		pipeline			パイプライン
		@param[in]		renderTarget		レンダーターゲット
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderQueue::RenderAll(MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget)
	{	
		for (auto& res : m_reserveList)
		{
			m_reservePointerList.push_back(&res);
		}
		std::sort(m_reservePointerList.begin(), m_reservePointerList.end(), [](const RENDER_DATA* lhs, const RENDER_DATA* rhs)
			{
				if(lhs->priority > rhs->priority) return true;
				if(lhs->priority < rhs->priority) return false;
				if(lhs->order < rhs->order) return true;
				return false;
			});
		do
		{
			auto cpuHandle = m_constantDescHeap->GetCPUDescriptorHandleForHeapStart();
			const size_t processNum = min(m_reservePointerList.size(), m_maxReserve);
			auto itr = m_reservePointerList.begin();
			for(int idx = 0; idx < processNum; ++idx, ++itr)
			{
				m_pDevice->GetDevice()->CopyDescriptorsSimple(1, cpuHandle,
					(*itr)->textureHeap->GetTextureHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
				cpuHandle.ptr += m_descriptorHeapIncrementSize * 2;
				*m_pMapMatrix[idx] = (*itr)->constData;
			}

			int beforeBlendType = -1;
			auto handle = m_constantDescHeap->GetGPUDescriptorHandleForHeapStart();
			itr = m_reservePointerList.begin();
			for(int idx = 0; idx < processNum; ++idx, ++itr)
			{
				renderTarget.SetRenderBaseCommand(cmdList);
					pipeline.SetPipelineState((*itr)->blendType, cmdList);
					beforeBlendType = (*itr)->blendType;
				cmdList.GetCommandList()->SetDescriptorHeaps(1, m_constantDescHeap.GetAddressOf());
				cmdList.GetCommandList()->SetGraphicsRootDescriptorTable(0, handle);

				cmdList.GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				cmdList.GetCommandList()->IASetVertexBuffers(0, 1, (*itr)->vertexBufferView);
				cmdList.GetCommandList()->DrawInstanced(4, 1, 0, 0);

				handle.ptr += m_descriptorHeapIncrementSize * 2;
			}
			m_reservePointerList.erase(m_reservePointerList.begin(), m_reservePointerList.begin() + processNum);
			cmdList.Execute();
		} while(!m_reservePointerList.empty());
		m_reserveList.clear();
	}

	/**********************************************************************//**
		@brief			指定したインデックスに定数バッファビューを構築する
		@param[in]		index				生成時に割り当てられたインデックス
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderQueue::_CreateCbv(uint32_t index, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = (sizeof(CONSTANT_DATA) + 0xFF) & ~0xFF;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc, D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(m_constantBuffers[index].ReleaseAndGetAddressOf()));

		auto basicHeapHandle = m_constantDescHeap->GetCPUDescriptorHandleForHeapStart();
		basicHeapHandle.ptr += m_descriptorHeapIncrementSize * (index * 2 + 1);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_constantBuffers[index]->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = static_cast<UINT>(m_constantBuffers[index]->GetDesc().Width);

		device.GetDevice()->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

		m_constantBuffers[index]->Map(0, nullptr, (void**)&m_pMapMatrix[index]);
	}

	/**********************************************************************//**
		@brief			定数バッファを初期化する
		@param[in]		device			デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderQueue::_InitalizeConstantBuffer(const MEGraphicDevice& device)
	{
		m_constantBuffers.resize(m_maxReserve);
		m_pMapMatrix.resize(m_maxReserve);
		for(int idx = 0; idx < m_maxReserve; ++idx)
		{
			_CreateCbv(idx, *m_pDevice);
		}
	}
}