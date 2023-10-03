//! @file GraphicCommandList.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicCommandList.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	GraphicCommandList::GraphicCommandList()
	{}

	/**********************************************************************//**
		@brief			������
		@param[in]		device			DX12�f�o�C�X
		@return			�C���X�^���X
	*//***********************************************************************/
	void GraphicCommandList::Initialize(ID3D12Device *device)
	{
		//DX12 �R�}���h���X�g�ƃR�}���h�A���P�[�^�[
		{
			auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator.ReleaseAndGetAddressOf()));
		}
		{
			auto result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(),
				nullptr, IID_PPV_ARGS(cmdList.ReleaseAndGetAddressOf()));
		}

		//DX12 �R�}���h�L���[
		{
			D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
			cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cmdQueueDesc.NodeMask = 0;
			cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			auto result = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(cmdQueue.ReleaseAndGetAddressOf()));
		}
	}
}