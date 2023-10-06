//! @file GraphicGpuResourceManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicGpuResourceManager.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEGraphicGpuResourceManager::MEGraphicGpuResourceManager(): m_constantBuffers(m_maxResourceView), m_textureBuffers(m_maxResourceView)
	{}

	/**********************************************************************//**
		@brief			初期化
		@param			device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::Initialize(const MEGraphicDevice& device)
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = m_maxResourceView * 2;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		auto result = device.GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_basicDescHeap.ReleaseAndGetAddressOf()));

		m_descriptorHeapIncrementSize = device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		_CreateVertexBuffer(4, device);
	}

	/**********************************************************************//**
		@brief			画像を読み込む
		@param[in]		filepath			読み込む画像のファイルパス
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	MEGraphicLoadedImage  MEGraphicGpuResourceManager::LoadGraph(const std::wstring& filepath,
		const MEGraphicDevice& device, MEGraphicCommandList& cmdList,
		MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget)
	{
		auto index = _GetShaderResourceIndex();
		_InitalizeConstantBuffer(index, device);

		DirectX::TexMetadata metadata = {};
		DirectX::ScratchImage scratchImg = {};
		DirectX::Image const* img = {};

		DirectX::LoadFromWICFile(filepath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratchImg);
		img = scratchImg.GetImage(0, 0, 0);

		_CreateTextureBuffer(index, metadata, device);
		_CreateCbv(index, device);
		_CreateSrv(index, img->format, device);

		_ResetUploadBuffer(img->rowPitch, img->height, device);
		_UploadDataToUploadBuffer(img->pixels, img->rowPitch, img->height);
		_UploadToGpu(index, metadata, img->rowPitch, img->format, cmdList);

		MEGraphicLoadedImage ret(index, img->width, img->height, &cmdList, this, &pipeline, &renderTarget);

		return ret;
	}

	/**********************************************************************//**
		@brief			描画時にディスクリプタヒープ等をコマンドリストに設定する
		@param[in]		index					描画する画像のインデックス
		@param[in]		cmdList					コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::SetGpuResource(const uint32_t index, MEGraphicCommandList& cmdList)
	{
		auto handle = m_basicDescHeap->GetGPUDescriptorHandleForHeapStart();
		handle.ptr += m_descriptorHeapIncrementSize * index * 2;
		cmdList.GetCommandList()->SetDescriptorHeaps(1, m_basicDescHeap.GetAddressOf());
		cmdList.GetCommandList()->SetGraphicsRootDescriptorTable(0, handle);
	}

	/**********************************************************************//**
		@brief			頂点データをバッファに書き込む
		@param[in]		vertices					頂点データの先頭のポインタ
		@param[in]		vertexNum					頂点の数
		@param[in]		cmdList						コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadVertexData(VERTEX_DATA* vertices, size_t vertexNum, MEGraphicCommandList& cmdList)
	{
		VERTEX_DATA* vertMap = nullptr;
		auto result = m_vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&vertMap));
		std::copy_n(vertices, vertexNum, vertMap);
		m_vertexBuffer->Unmap(0, nullptr);
	}

	/**********************************************************************//**
		@brief			定数バッファに書き込む
		@param[in]		matrix						変形行列
		@param[in]		cmdList						コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadConstantData(const uint32_t index, DirectX::XMMATRIX matrix, MEGraphicCommandList& cmdList)
	{
		DirectX::XMMATRIX* mapMatrix;
		auto result = m_constantBuffers[index]->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = matrix;
		m_constantBuffers[index]->Unmap(0, nullptr);
	}

	/**********************************************************************//**
		@brief			描画対象としてセットする
		@param[in]		cmdList						コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::SetRenderCommand(MEGraphicCommandList& cmdList)
	{
		cmdList.GetCommandList()->IASetVertexBuffers(0, 1, &m_vertexBufferView);
		cmdList.GetCommandList()->DrawInstanced(4, 1, 0, 0);
	}

	/**********************************************************************//**
		@brief			シェーダーリソースビューと定数バッファビューを生成しても良いインデックスを返す
		@param			なし
		@return			シェーダーリソースビューを生成しても良いインデックス(+1すると定数バッファ)
	*//***********************************************************************/
	uint32_t MEGraphicGpuResourceManager::_GetShaderResourceIndex()
	{
		if(m_currentIndex >= m_maxResourceView)
		{
			return -1;
		}
		return m_currentIndex++;
	}

	/**********************************************************************//**
		@brief			指定したインデックスにシェーダーリソースビューを構築する
		@param[in]		index				生成時に割り当てられたインデックス
		@param[in]		format				画像のフォーマット
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_CreateSrv(uint32_t index, const DXGI_FORMAT format,
		const MEGraphicDevice& device)
	{
		auto basicHeapHandle = m_basicDescHeap->GetCPUDescriptorHandleForHeapStart();
		basicHeapHandle.ptr += m_descriptorHeapIncrementSize * (index * 2);

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		device.GetDevice()->CreateShaderResourceView(m_textureBuffers[index].Get(), &srvDesc, basicHeapHandle);
	}

	/**********************************************************************//**
		@brief			指定したインデックスに定数バッファビューを構築する
		@param[in]		index				生成時に割り当てられたインデックス
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_CreateCbv(uint32_t index, const MEGraphicDevice& device)
	{
		auto basicHeapHandle = m_basicDescHeap->GetCPUDescriptorHandleForHeapStart();
		basicHeapHandle.ptr += m_descriptorHeapIncrementSize * (index * 2 + 1);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_constantBuffers[index]->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = m_constantBuffers[index]->GetDesc().Width;

		device.GetDevice()->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
	}

	/**********************************************************************//**
		@brief			テクスチャのバッファを作成する
		@param[in]		index				生成時に割り当てられたインデックス
		@param[in]		metadata			画像のメタデータ
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_CreateTextureBuffer(const uint32_t index,
		const DirectX::TexMetadata& metadata, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_DEFAULT;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
		resdesc.Width = metadata.width;
		resdesc.Height = metadata.height;
		resdesc.DepthOrArraySize = metadata.arraySize;
		resdesc.MipLevels = metadata.mipLevels;
		resdesc.Format = metadata.format;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(m_textureBuffers[index].ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			アップロード用のバッファを再設定する
		@param[in]		rowPitch			画像の一行辺りのデータサイズ
		@param[in]		height			画像の高さ
		@param[in]		device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = _GetAlignmentedSize(rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * height;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(m_uploadBuffer.ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			中間バッファにデータをアップロードする
		@param[in]		srcData			画像の生データへのポインタ
		@param[in]		rowPitch		画像の一行辺りのデータサイズ
		@param[in]		height			画像の高さ
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_UploadDataToUploadBuffer(uint8_t * srcData, const size_t rowPitch, const size_t height)
	{
		uint8_t* mapforImg = nullptr;
		auto result = m_uploadBuffer->Map(0, nullptr, (void**)&mapforImg);

		auto srcAddress = srcData;
		auto GpuRowPitch = _GetAlignmentedSize(rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
		for(int y = 0; y < height; ++y)
		{
			std::copy_n(srcAddress, GpuRowPitch, mapforImg);
			srcAddress += rowPitch;
			mapforImg += GpuRowPitch;
		}
		m_uploadBuffer->Unmap(0, nullptr);
	}

	/**********************************************************************//**
		@brief			テクスチャデータを転送する直前にバリアを設定する
		@param[in]		index						対象のバッファのインデックス
		@param[in]		cmdList						コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_SetBarrierBeforeUploadTexture(uint32_t index, const MEGraphicCommandList& cmdList)
	{
		D3D12_RESOURCE_BARRIER barrierDesc = {};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_textureBuffers[index].Get();
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		cmdList.GetCommandList()->ResourceBarrier(1, &barrierDesc);
	}

	/**********************************************************************//**
		@brief			頂点バッファを作成する
		@param[in]		vertexNum					頂点の数(もし3D描画に対応するつもりならこれは画像の枚数だけ必要)
		@param[in]		device						デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = sizeof(VERTEX_DATA) * vertexNum;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(m_vertexBuffer.ReleaseAndGetAddressOf()));

		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = sizeof(VERTEX_DATA) * vertexNum;
		m_vertexBufferView.StrideInBytes = sizeof(VERTEX_DATA);
	}

	/**********************************************************************//**
		@brief			テクスチャデータを転送する
		@param[in]		index						対象のバッファのインデックス
		@param[in]		metadata					画像のメタデータ
		@param[in]		rowPitch					画像データの行単位のサイズ
		@param[in]		format						画像データのフォーマット
		@param[in]		cmdList						コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_UploadToGpu(uint32_t index, DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
		MEGraphicCommandList& cmdList)
	{
		D3D12_TEXTURE_COPY_LOCATION src = {};
		src.pResource = m_uploadBuffer.Get();
		src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset = 0;
		src.PlacedFootprint.Footprint.Width = metadata.width;
		src.PlacedFootprint.Footprint.Height = metadata.height;
		src.PlacedFootprint.Footprint.Depth = metadata.depth;
		src.PlacedFootprint.Footprint.RowPitch = _GetAlignmentedSize(rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
		src.PlacedFootprint.Footprint.Format = format;

		D3D12_TEXTURE_COPY_LOCATION dst = {};
		dst.pResource = m_textureBuffers[index].Get();
		dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex = 0;

		cmdList.GetCommandList()->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

		_SetBarrierBeforeUploadTexture(index, cmdList);
		cmdList.Execute();
	}

	/**********************************************************************//**
		@brief			定数バッファを初期化する
		@param[in]		index			生成時に割り当てられたインデックス
		@param[in]		device			デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_InitalizeConstantBuffer(uint32_t index, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = (sizeof(DirectX::XMMATRIX) + 0xFF) & ~0xFF;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(m_constantBuffers[index].ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief	アライメントに揃える
		@param size			元のサイズ
		@param alignment		アライメントサイズ
		@return				アライメントを揃えたサイズ
	*//***********************************************************************/
	size_t MEGraphicGpuResourceManager::_GetAlignmentedSize(size_t size, size_t alignment)
	{
		return size + alignment - size % alignment;
	}
}
