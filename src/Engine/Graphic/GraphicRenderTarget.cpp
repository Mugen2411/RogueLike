#include "GraphicRenderTarget.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEGraphicRenderTarget::MEGraphicRenderTarget() :m_numBackBuffer(2), m_backBuffers(m_numBackBuffer)
	{}

	/**********************************************************************//**
		@brief			初期化
		@param[in]		device				デバイス
		@param[in]		cmdList				コマンドリスト
		@param[in]		hwnd				ウィンドウハンドル
		@param[in]		window_width		ウィンドウ(描画範囲)の横幅
		@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
		@return			インスタンス
	*//***********************************************************************/
	void MEGraphicRenderTarget::Initialize(const MEGraphicDevice& device, const MEGraphicCommandList& cmdList,
		HWND hwnd, const int window_width, const int window_height)
	{
		//DX12 スワップチェイン
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

			auto result = device.GetFactory()->CreateSwapChainForHwnd(cmdList.GetCommandQueue(), hwnd, &swapchainDesc,
				nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(m_swapchain.ReleaseAndGetAddressOf()));
		}
		//DX12 ディスクリプタヒープ
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

			for(uint32_t idx = 0; idx < swcDesc.BufferCount; ++idx)
			{
				result = m_swapchain->GetBuffer(idx, IID_PPV_ARGS(m_backBuffers[idx].ReleaseAndGetAddressOf()));
				device.GetDevice()->CreateRenderTargetView(m_backBuffers[idx].Get(), nullptr, handle);
				handle.ptr += device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			}
		}
		{
			m_viewport.Width = static_cast<float>(window_width);
			m_viewport.Height = static_cast<float>(window_height);
			m_viewport.TopLeftX = 0;
			m_viewport.TopLeftY = 0;
			m_viewport.MaxDepth = 1.0f;
			m_viewport.MinDepth = 0.0f;
		}
	}

	/**********************************************************************//**
		@brief			バックバッファの内容をディスプレイに反映する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::Present()
	{
		m_swapchain->Present(1, 0);
	}

	/**********************************************************************//**
		@brief			描画前バリア
		@param			device			デバイス
		@param			cmdList			コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetBarrierBeforeRender(MEGraphicDevice& device, MEGraphicCommandList& cmdList)
	{
		//DX12 プレゼント前バリア
		{
			auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
			D3D12_RESOURCE_BARRIER BarrierDesc = {};
			BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			BarrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
			BarrierDesc.Transition.Subresource = 0;
			BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			cmdList.GetCommandList()->ResourceBarrier(1, &BarrierDesc);

			cmdList.Execute();

			m_renderTargetHandle = m_rtvHeaps->GetCPUDescriptorHandleForHeapStart();
			m_renderTargetHandle.ptr += bbIdx * device.GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}

	/**********************************************************************//**
		@brief			プレゼント前バリア
		@param			cmdList			コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetBarrierBeforePresent(MEGraphicCommandList& cmdList)
	{
		//DX12 プレゼント前バリア
		{
			auto bbIdx = m_swapchain->GetCurrentBackBufferIndex();
			D3D12_RESOURCE_BARRIER BarrierDesc = {};
			BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			BarrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
			BarrierDesc.Transition.Subresource = 0;
			BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
			BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
			cmdList.GetCommandList()->ResourceBarrier(1, &BarrierDesc);

			cmdList.Execute();
		}
	}

	/**********************************************************************//**
		@brief			画面を指定した色でクリアする
		@param			clearColor		指定色(RGBA, 0.0f〜1.0f)
		@param			cmdList			コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::Clear(float clearColor[4], MEGraphicCommandList& cmdList)
	{
		cmdList.GetCommandList()->OMSetRenderTargets(1, &m_renderTargetHandle, true, nullptr);
		cmdList.GetCommandList()->ClearRenderTargetView(m_renderTargetHandle, clearColor, 0, nullptr);
	}

	/**********************************************************************//**
		@brief			描画可能な範囲を設定する
		@param			cmdList			コマンドリスト
		@param[in]		topX			左上のX座標
		@param[in]		topY			左上のY座標
		@param[in]		bottomX			右下のX座標
		@param[in]		bottomY			右下のY座標
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetRenderArea(MEGraphicCommandList& cmdList, 
		const int topX, const int topY, const int bottomX, const int bottomY)
	{
		m_scissorRect.top = topY;
		m_scissorRect.left = topX;
		m_scissorRect.right = bottomX;
		m_scissorRect.bottom = bottomY;
	}

	/**********************************************************************//**
		@brief			描画毎に必要なコマンドを積む
		@param			cmdList			コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicRenderTarget::SetRenderBaseCommand(MEGraphicCommandList& cmdList)
	{
		cmdList.GetCommandList()->OMSetRenderTargets(1, &m_renderTargetHandle, true, nullptr);
		cmdList.GetCommandList()->RSSetScissorRects(1, &m_scissorRect);
		cmdList.GetCommandList()->RSSetViewports(1, &m_viewport);
	}
}
