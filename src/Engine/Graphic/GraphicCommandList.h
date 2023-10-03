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
	class GraphicCommandList
	{
	public:
		//! コンストラクタ
		GraphicCommandList();
		//! 初期化
		void Initialize(ID3D12Device* device);
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator = nullptr;		//!< コマンドアロケーター
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = nullptr;		//!< コマンドリスト
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue = nullptr;				//!< コマンドキュー
	};
}

#endif//__MugenEngine_GraphicCommandList__