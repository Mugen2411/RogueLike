//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderTarget__
#define __MugenEngine_GraphicRenderTarget__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"

#include <vector>

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicRenderTarget
		@brief		描画対象となる画面を管理するクラス
	*//***********************************************************************/
	class MEGraphicRenderTarget
	{
	public:
		//! コンストラクタ
		MEGraphicRenderTarget();
		//! 初期化
		void Initialize(IDXGIFactory4* dxgiFactory, ID3D12CommandQueue* cmdQueue,
			HWND hwnd, const int window_width, const int window_height);
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< スワップチェイン
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< レンダーターゲットヒープ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< バックバッファ
	};
}

#endif//__MugenEngine_GraphicRenderTarget__