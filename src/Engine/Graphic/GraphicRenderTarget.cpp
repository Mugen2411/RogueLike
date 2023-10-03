#include "GraphicRenderTarget.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicRenderTarget::MEGraphicRenderTarget() :m_numBackBuffer(2), m_backBuffers(m_numBackBuffer)
	{}

	/**********************************************************************//**
		@brief			������
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�C���X�^���X
	*//***********************************************************************/
	void MEGraphicRenderTarget::Initialize(const MEGraphicDevice& device, ID3D12CommandQueue* cmdQueue,
		HWND hwnd, const int window_width, const int window_height)
	{
		//DX12 �X���b�v�`�F�C��
		{
			DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

			swapchainDesc.Width = window_width;
			swapchainDesc.Height = window_height;
			swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapchainDesc.Stereo = false;
			swapchainDesc.SampleDesc.Count = 1;
			swapchainDesc.SampleDesc.Quality = 0;
			swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
			swapchainDesc.BufferCount = 2;
			swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
			swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			auto result = device.GetFactory()->CreateSwapChainForHwnd(cmdQueue, hwnd, &swapchainDesc,
				nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(m_swapchain.ReleaseAndGetAddressOf()));
		}
		//DX12 �f�B�X�N���v�^�q�[�v
		{
			D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
			heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			heapDesc.NodeMask = 0;
			heapDesc.NumDescriptors = 2;
			heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			auto result = device.GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_rtvHeaps.ReleaseAndGetAddressOf()));

			DXGI_SWAP_CHAIN_DESC swcDesc = {};
			m_swapchain->GetDesc(&swcDesc);

			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvHeaps->GetCPUDescriptorHandleForHeapStart();

			for(int idx = 0; idx < swcDesc.BufferCount; ++idx)
			{
				result = m_swapchain->GetBuffer(idx, IID_PPV_ARGS(m_backBuffers[idx].ReleaseAndGetAddressOf()));
				device.GetDevice()->CreateRenderTargetView(m_backBuffers[idx].Get(), nullptr, handle);
				handle.ptr += device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			}
		}
	}

	/**********************************************************************//**
		@brief			�o�b�N�o�b�t�@�̓��e���f�B�X�v���C�ɔ��f����
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicRenderTarget::Present()
	{
		m_swapchain->Present(1, 0);
	}

	/**********************************************************************//**
		@brief			�`��O�o���A
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetBarrierBeforeRender(ID3D12GraphicsCommandList* cmdList)
	{
		//DX12 �v���[���g�O�o���A
		{
			auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
			D3D12_RESOURCE_BARRIER BarrierDesc = {};
			BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			BarrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
			BarrierDesc.Transition.Subresource = 0;
			BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			cmdList->ResourceBarrier(1, &BarrierDesc);
		}
	}

	/**********************************************************************//**
		@brief			�v���[���g�O�o���A
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetBarrierBeforePresent(ID3D12GraphicsCommandList* cmdList)
	{
		//DX12 �v���[���g�O�o���A
		{
			auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
			D3D12_RESOURCE_BARRIER BarrierDesc = {};
			BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			BarrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
			BarrierDesc.Transition.Subresource = 0;
			BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
			BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
			cmdList->ResourceBarrier(1, &BarrierDesc);
		}
	}
}
