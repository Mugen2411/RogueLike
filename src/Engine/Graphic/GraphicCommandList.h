//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCommandList__
#define __MugenEngine_GraphicCommandList__

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicCommandList
		@brief		GPUコマンドを管理するクラス
	*//***********************************************************************/
	class MEGraphicCommandList
	{
	public:
		//! コンストラクタ
		MEGraphicCommandList();
		//! 初期化
		void Initialize(ID3D12Device * const device);
		//! 実行&GPU処理を待機
		void Execute();
		//! コマンドキューの生ポインタを取得
		ID3D12CommandQueue * const GetCommandQueue() const;
		//! コマンドリストの生ポインタを取得
		ID3D12GraphicsCommandList* const GetCommandList() const;
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;		//!< コマンドアロケーター
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;		//!< コマンドリスト
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;				//!< コマンドキュー

		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence = nullptr;						//!< フェンス
		UINT64 m_fenceVal = 0;														//!< フェンスの進捗を管理する数値
	};
}

#endif//__MugenEngine_GraphicCommandList__