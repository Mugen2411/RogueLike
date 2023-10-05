//! @file GraphicCommandList.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicCommandList.h"
#include "GraphicDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicCommandList::MEGraphicCommandList()
	{}

	/**********************************************************************//**
		@brief			������
		@param[in]		device			DX12�f�o�C�X
		@return			�C���X�^���X
	*//***********************************************************************/
	void MEGraphicCommandList::Initialize(const MEGraphicDevice& device)
	{
		//DX12 �R�}���h���X�g�ƃR�}���h�A���P�[�^�[
		{
			auto result = device.GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_cmdAllocator.ReleaseAndGetAddressOf()));
		}
		{
			auto result = device.GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator.Get(),
				nullptr, IID_PPV_ARGS(m_cmdList.ReleaseAndGetAddressOf()));
		}

		//DX12 �R�}���h�L���[
		{
			D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
			cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cmdQueueDesc.NodeMask = 0;
			cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

			auto result = device.GetDevice()->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_cmdQueue.ReleaseAndGetAddressOf()));
		}

		//�t�F���X
		{
			auto result = device.GetDevice()->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf()));
		}
	}

	/**********************************************************************//**
		@brief			�R�}���h�����s����GPU�������I���܂őҋ@����
		@param[in]		�Ȃ�
		@return			�Ȃ�
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
		@brief			�R�}���h�L���[�̐��|�C���^���擾
		@param			�Ȃ�
		@return			�R�}���h�L���[�̐��|�C���^
	*//***********************************************************************/
	ID3D12CommandQueue * const MEGraphicCommandList::GetCommandQueue() const
	{
		return m_cmdQueue.Get();
	}

	/**********************************************************************//**
		@brief			�R�}���h���X�g�̐��|�C���^���擾
		@param			�Ȃ�
		@return			�R�}���h���X�g�̐��|�C���^
	*//***********************************************************************/
	ID3D12GraphicsCommandList* const MEGraphicCommandList::GetCommandList() const
	{
		return m_cmdList.Get();
	}
}