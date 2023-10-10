//! @file GraphicGpuResourceManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicGpuResourceManager.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicGpuResourceManager::MEGraphicGpuResourceManager()
	{}

	/**********************************************************************//**
		@brief			������
		@param			device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::Initialize(const MEGraphicDevice& device, UINT numVertexBuffer)
	{
		m_numVertexBuffer = numVertexBuffer;
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = 2;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		auto result = device.GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_basicDescHeap.ReleaseAndGetAddressOf()));

		if(FAILED(result))
		{
			OutputDebugStringA("DX12 DescriptorHeap Initialize Error.\n");
		}

		m_descriptorHeapIncrementSize = device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		CreateVertexBuffer(4, device);
		_InitalizeConstantBuffer(device);
		_CreateCbv(device);
	}

	/**********************************************************************//**
		@brief			�`�掞�Ƀf�B�X�N���v�^�q�[�v�����R�}���h���X�g�ɐݒ肷��
		@param[in]		cmdList					�R�}���h���X�g
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::SetGpuResource(MEGraphicCommandList& cmdList)
	{
		auto handle = m_basicDescHeap->GetGPUDescriptorHandleForHeapStart();
		cmdList.GetCommandList()->SetDescriptorHeaps(1, m_basicDescHeap.GetAddressOf());
		cmdList.GetCommandList()->SetGraphicsRootDescriptorTable(0, handle);
	}

	/**********************************************************************//**
		@brief			���_�f�[�^���o�b�t�@�ɏ�������
		@param[in]		vertices					���_�f�[�^�̐擪�̃|�C���^
		@param[in]		vertexNum					���_�̐�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadVertexData(uint32_t index, VERTEX_DATA* vertices, size_t vertexNum)
	{
		VERTEX_DATA* vertMap = nullptr;
		auto result = m_vertexBuffer[index]->Map(0, nullptr, reinterpret_cast<void**>(&vertMap));
		if(FAILED(result))
		{
			OutputDebugStringA("DX12 VertexBuffer Mapping Error.\n");
		}
		std::copy_n(vertices, vertexNum, vertMap);
		m_vertexBuffer[index]->Unmap(0, nullptr);
	}

	/**********************************************************************//**
		@brief			�萔�o�b�t�@�ɏ�������
		@param[in]		matrix						�ό`�s��
		@param[in]		cmdList						�R�}���h���X�g
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadConstantData(CONSTANT_DATA& constData)
	{
		CONSTANT_DATA* mapMatrix;
		auto result = m_constantBuffer->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = constData;
		m_constantBuffer->Unmap(0, nullptr);
	}

	/**********************************************************************//**
		@brief			�V�F�[�_�[���\�[�X�r���[���\�z����
		@param[in]		format				�摜�̃t�H�[�}�b�g
		@param[in]		device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::CreateSrv(const DXGI_FORMAT format,
		const MEGraphicDevice& device)
	{
		auto basicHeapHandle = m_basicDescHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		device.GetDevice()->CreateShaderResourceView(m_textureBuffer.Get(), &srvDesc, basicHeapHandle);
	}

	/**********************************************************************//**
		@brief			�w�肵���C���f�b�N�X�ɒ萔�o�b�t�@�r���[���\�z����
		@param[in]		index				�������Ɋ��蓖�Ă�ꂽ�C���f�b�N�X
		@param[in]		device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_CreateCbv(const MEGraphicDevice& device)
	{
		auto basicHeapHandle = m_basicDescHeap->GetCPUDescriptorHandleForHeapStart();
		basicHeapHandle.ptr += m_descriptorHeapIncrementSize;

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = static_cast<UINT>(m_constantBuffer->GetDesc().Width);

		device.GetDevice()->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
	}

	/**********************************************************************//**
		@brief			�e�N�X�`���̃o�b�t�@���쐬����
		@param[in]		metadata			�摜�̃��^�f�[�^
		@param[in]		device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::CreateTextureBuffer(const DirectX::TexMetadata& metadata, const MEGraphicDevice& device)
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
		resdesc.Width = metadata.width;
		resdesc.Height = static_cast<UINT>(metadata.height);
		resdesc.DepthOrArraySize = static_cast<UINT16>(metadata.arraySize);
		resdesc.MipLevels = static_cast<UINT16>(metadata.mipLevels);
		resdesc.Format = metadata.format;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, nullptr, IID_PPV_ARGS(m_textureBuffer.ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			�A�b�v���[�h�p�̃o�b�t�@���Đݒ肷��
		@param[in]		rowPitch			�摜�̈�s�ӂ�̃f�[�^�T�C�Y
		@param[in]		height			�摜�̍���
		@param[in]		device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device)
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
		@brief			���ԃo�b�t�@�Ƀf�[�^���A�b�v���[�h����
		@param[in]		srcData			�摜�̐��f�[�^�ւ̃|�C���^
		@param[in]		rowPitch		�摜�̈�s�ӂ�̃f�[�^�T�C�Y
		@param[in]		height			�摜�̍���
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadDataToUploadBuffer(uint8_t * srcData, const size_t rowPitch, const size_t height)
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
		@brief			�e�N�X�`���f�[�^��]�����钼�O�Ƀo���A��ݒ肷��
		@param[in]		cmdList						�R�}���h���X�g
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_SetBarrierBeforeUploadTexture(const MEGraphicCommandList& cmdList)
	{
		D3D12_RESOURCE_BARRIER barrierDesc = {};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_textureBuffer.Get();
		barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		cmdList.GetCommandList()->ResourceBarrier(1, &barrierDesc);
	}

	/**********************************************************************//**
		@brief			���_�o�b�t�@���쐬����
		@param[in]		vertexNum					���_�̐�(����3D�`��ɑΉ��������Ȃ炱��͉摜�̖��������K�v)
		@param[in]		device						�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device)
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

		m_vertexBuffer.resize(m_numVertexBuffer);
		m_vertexBufferView.resize(m_numVertexBuffer);
		for(UINT idx = 0; idx < m_numVertexBuffer; ++idx)
		{
			auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(m_vertexBuffer[idx].ReleaseAndGetAddressOf()));

			m_vertexBufferView[idx].BufferLocation = m_vertexBuffer[idx]->GetGPUVirtualAddress();
			m_vertexBufferView[idx].SizeInBytes = static_cast<UINT>(sizeof(VERTEX_DATA) * vertexNum);
			m_vertexBufferView[idx].StrideInBytes = sizeof(VERTEX_DATA);
		}
	}

	/**********************************************************************//**
		@brief			�e�N�X�`���f�[�^��]������
		@param[in]		metadata					�摜�̃��^�f�[�^
		@param[in]		rowPitch					�摜�f�[�^�̍s�P�ʂ̃T�C�Y
		@param[in]		format						�摜�f�[�^�̃t�H�[�}�b�g
		@param[in]		cmdList						�R�}���h���X�g
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::UploadToGpu(DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
		MEGraphicCommandList& cmdList)
	{
		D3D12_TEXTURE_COPY_LOCATION src = {};
		src.pResource = m_uploadBuffer.Get();
		src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset = 0;
		src.PlacedFootprint.Footprint.Width = static_cast<UINT>(metadata.width);
		src.PlacedFootprint.Footprint.Height = static_cast<UINT>(metadata.height);
		src.PlacedFootprint.Footprint.Depth = static_cast<UINT>(metadata.depth);
		src.PlacedFootprint.Footprint.RowPitch = static_cast<UINT>(_GetAlignmentedSize(rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT));
		src.PlacedFootprint.Footprint.Format = format;

		D3D12_TEXTURE_COPY_LOCATION dst = {};
		dst.pResource = m_textureBuffer.Get();
		dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex = 0;

		cmdList.GetCommandList()->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

		_SetBarrierBeforeUploadTexture(cmdList);
		cmdList.Execute();
	}

	void MEGraphicGpuResourceManager::UploadByCpu(uint8_t *srcData, size_t rowPitch, size_t height)
	{
		auto result = m_textureBuffer->WriteToSubresource(0, nullptr, srcData,
			static_cast<UINT>(rowPitch), static_cast<UINT>(rowPitch * height));
	}

	/**********************************************************************//**
		@brief			�萔�o�b�t�@������������
		@param[in]		device			�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicGpuResourceManager::_InitalizeConstantBuffer(const MEGraphicDevice& device)
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

		auto result = device.GetDevice()->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(m_constantBuffer.ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief	�A���C�����g�ɑ�����
		@param size			���̃T�C�Y
		@param alignment		�A���C�����g�T�C�Y
		@return				�A���C�����g�𑵂����T�C�Y
	*//***********************************************************************/
	size_t MEGraphicGpuResourceManager::_GetAlignmentedSize(size_t size, size_t alignment)
	{
		return size + alignment - size % alignment;
	}
}
