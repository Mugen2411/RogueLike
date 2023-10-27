//! @file GraphicCommandList.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicCommandList.h"
#include "GraphicDevice.h"

namespace mugen_engine
{
	MEGraphicCommandList::MEGraphicCommandList()
	{}

	void MEGraphicCommandList::Initialize(const MEGraphicDevice& device)
	{
		//DX12 �R�}���h���X�g�ƃR�}���h�A���P�[�^�[
		{
			auto result = device.GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdAllocator.ReleaseAndGetAddressOf()));
			if(FAILED(result))
			{
				OutputDebugStringA("DX12 CommandAllocator Initialize Error.\n");
			}
		}
		{
			auto result = device.GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(),
				nullptr, IID_PPV_ARGS(m_cmdList.ReleaseAndGetAddressOf()));
			if(FAILED(result))
			{
				OutputDebugStringA("DX12 CommandList Initialize Error.\n");
			}
		}

		//DX12 �R�}���h�L���[
		{
			D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
			cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cmdQueueDesc.NodeMask = 0;
			cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			auto result = device.GetDevice()->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_cmdQueue.ReleaseAndGetAddressOf()));
			if(FAILED(result))
			{
				OutputDebugStringA("DX12 CommandQueue Initialize Error.\n");
			}
		}

		//�t�F���X
		{
			auto result = device.GetDevice()->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf()));
			if(FAILED(result))
			{
				OutputDebugStringA("DX12 Fence Initialize Error.\n");
			}
		}
	}

	void MEGraphicCommandList::Execute()
	{
		m_cmdList->Close();

		static ID3D12CommandList* cmdlists[] = { m_cmdList.Get() };
		m_cmdQueue->ExecuteCommandLists(1, cmdlists);

		m_cmdQueue->Signal(m_fence.Get(), ++m_fenceVal);
		if(m_fence->GetCompletedValue() < m_fenceVal)
		{
			static HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			m_fence->SetEventOnCompletion(m_fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			//CloseHandle(event);
		}

		m_cmdAllocator->Reset();
		m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
	}
}