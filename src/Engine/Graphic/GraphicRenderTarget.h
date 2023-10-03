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
		void Initialize(const MEGraphicDevice& device, ID3D12CommandQueue* cmdQueue,
			HWND hwnd, const int window_width, const int window_height);
		//! バックバッファの内容をディスプレイに反映する
		void Present();
		//! 描画前バリア
		void SetBarrierBeforeRender(MEGraphicDevice& device, MEGraphicCommandList& cmdList);
		//! プレゼント前バリア
		void SetBarrierBeforePresent(MEGraphicCommandList& cmdList);
		//! 画面を指定した色でクリアする
		void Clear(float clearColor[4], MEGraphicCommandList& cmdList);
	private:
		const int m_numBackBuffer;												//!< バックバッファの数
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< スワップチェイン
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< レンダーターゲットヒープ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< バックバッファ
		D3D12_CPU_DESCRIPTOR_HANDLE m_renderTargetHandle;						//!< OMSetRenderTargetに渡すCPU上のアドレス
		D3D12_VIEWPORT m_viewport;												//!< ビューポート
	};
}

#endif//__MugenEngine_GraphicRenderTarget__