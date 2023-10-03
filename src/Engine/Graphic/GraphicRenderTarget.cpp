#include "GraphicRenderTarget.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicRenderTarget::MEGraphicRenderTarget() :m_backBuffers(2)
	{}

	/**********************************************************************//**
		@brief			������
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�C���X�^���X
	*//***********************************************************************/
	void MEGraphicRenderTarget::Initialize(IDXGIFactory4* dxgiFactory, ID3D12CommandQueue* cmdQueue,
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

			auto result = dxgiFactory->CreateSwapChainForHwnd(cmdQueue, hwnd, &swapchainDesc,
				nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(m_swapchain.ReleaseAndGetAddressOf()));
		}
	}
}
