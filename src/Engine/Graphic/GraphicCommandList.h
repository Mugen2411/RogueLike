//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCommandList__
#define __MugenEngine_GraphicCommandList__

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	class MEGraphicDevice;

	/**********************************************************************//**
		@class		MEGraphicCommandList
		@brief		GPUコマンドを管理するクラス
	*//***********************************************************************/
	class MEGraphicCommandList
	{
	public:
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicCommandList();

		/**********************************************************************//**
			@brief			初期化
			@param[in]		device			DX12デバイス
			@return			インスタンス
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			コマンドを実行してGPU処理が終わるまで待機する
			@param[in]		なし
			@return			なし
		*//***********************************************************************/
		void Execute();

		/**********************************************************************//**
			@brief			コマンドキューの生ポインタを取得
			@param			なし
			@return			コマンドキューの生ポインタ
		*//***********************************************************************/
		ID3D12CommandQueue* const GetCommandQueue() const
		{
			return m_cmdQueue.Get();
		}

		/**********************************************************************//**
			@brief			コマンドリストの生ポインタを取得
			@param			なし
			@return			コマンドリストの生ポインタ
		*//***********************************************************************/
		ID3D12GraphicsCommandList* const GetCommandList() const
		{
			return m_cmdList.Get();
		}
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;		//!< コマンドアロケーター
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;		//!< コマンドリスト
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;				//!< コマンドキュー

		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence = nullptr;						//!< フェンス
		UINT64 m_fenceVal = 0;														//!< フェンスの進捗を管理する数値
	};
}

#endif//__MugenEngine_GraphicCommandList__