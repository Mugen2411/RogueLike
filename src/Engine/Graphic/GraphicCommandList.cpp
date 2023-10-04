//! @file GraphicCommandList.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicCommandList.h"
#include "GraphicDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEGraphicCommandList::MEGraphicCommandList()
	{}

	/**********************************************************************//**
		@brief			初期化
		@param[in]		device			DX12デバイス
		@return			インスタンス
	*//***********************************************************************/
	void MEGraphicCommandList::Initialize(const MEGraphicDevice& device)
	{
		//DX12 コマンドリストとコマンドアロケーター
		{
			auto result = device.GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdAllocator.ReleaseAndGetAddressOf()));
		}
		{
			auto result = device.GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(),
				nullptr, IID_PPV_ARGS(m_cmdList.ReleaseAndGetAddressOf()));
		}

		//DX12 コマンドキュー
		{
			D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
			cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cmdQueueDesc.NodeMask = 0;
			cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			auto result = device.GetDevice()->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_cmdQueue.ReleaseAndGetAddressOf()));
		}

		//フェンス
		{
			auto result = device.GetDevice()->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf()));
		}
	}

	/**********************************************************************//**
		@brief			コマンドを実行してGPU処理が終わるまで待機する
		@param[in]		なし
		@return			なし
	*//***********************************************************************/
	void MEGraphicCommandList::Execute()
	{
		m_cmdList->Close();

		ID3D12CommandList* cmdlists[] = { m_cmdList.Get() };
		m_cmdQueue->ExecuteCommandLists(1, cmdlists);

		m_cmdQueue->Signal(m_fence.Get(), ++m_fenceVal);
		if(m_fence->GetCompletedValue() != m_fenceVal)
		{
			auto event = CreateEvent(nullptr, false, false, nullptr);
			m_fence->SetEventOnCompletion(m_fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		m_cmdAllocator->Reset();
		m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
	}

	/**********************************************************************//**
		@brief			コマンドキューの生ポインタを取得
		@param			なし
		@return			コマンドキューの生ポインタ
	*//***********************************************************************/
	ID3D12CommandQueue * const MEGraphicCommandList::GetCommandQueue() const
	{
		return m_cmdQueue.Get();
	}

	/**********************************************************************//**
		@brief			コマンドリストの生ポインタを取得
		@param			なし
		@return			コマンドリストの生ポインタ
	*//***********************************************************************/
	ID3D12GraphicsCommandList* const MEGraphicCommandList::GetCommandList() const
	{
		return m_cmdList.Get();
	}
}