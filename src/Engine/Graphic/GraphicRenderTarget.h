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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicRenderTarget();

		/**********************************************************************//**
			@brief			初期化
			@param[in]		device				デバイス
			@param[in]		cmdList				コマンドリスト
			@param[in]		hwnd				ウィンドウハンドル
			@param[in]		window_width		ウィンドウ(描画範囲)の横幅
			@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
			@return			インスタンス
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const MEGraphicCommandList& cmdList,
			HWND hwnd, const int window_width, const int window_height);

		/**********************************************************************//**
			@brief			バックバッファの内容をディスプレイに反映する
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Present();

		/**********************************************************************//**
			@brief			描画前バリア
			@param			device			デバイス
			@param			cmdList			コマンドリスト
			@return			なし
		*//***********************************************************************/
		void SetBarrierBeforeRender(MEGraphicDevice& device, MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			プレゼント前バリア
			@param			cmdList			コマンドリスト
			@return			なし
		*//***********************************************************************/
		void SetBarrierBeforePresent(MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			画面を指定した色でクリアする
			@param			clearColor		指定色(RGBA, 0.0f～1.0f)
			@param			cmdList			コマンドリスト
			@return			なし
		*//***********************************************************************/
		void Clear(float clearColor[4], MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			描画可能な範囲を設定する
			@param			cmdList			コマンドリスト
			@param[in]		topX			左上のX座標
			@param[in]		topY			左上のY座標
			@param[in]		bottomX			右下のX座標
			@param[in]		bottomY			右下のY座標
			@return			なし
		*//***********************************************************************/
		void SetRenderArea(MEGraphicCommandList& cmdList, 
			const int topX, const int topY, const int bottomX, const int bottomY);

		/**********************************************************************//**
			@brief			描画毎に必要なコマンドを積む
			@param			cmdList			コマンドリスト
			@return			なし
		*//***********************************************************************/
		void SetRenderBaseCommand(MEGraphicCommandList& cmdList);
	private:
		const int m_numBackBuffer;												//!< バックバッファの数
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< スワップチェイン
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< レンダーターゲットヒープ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< バックバッファ
		D3D12_CPU_DESCRIPTOR_HANDLE m_renderTargetHandle;						//!< OMSetRenderTargetに渡すCPU上のアドレス
		D3D12_VIEWPORT m_viewport;												//!< ビューポート
		D3D12_RECT m_scissorRect;												//!< シザー矩形
	};
}

#endif//__MugenEngine_GraphicRenderTarget__