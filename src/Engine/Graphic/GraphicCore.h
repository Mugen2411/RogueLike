//! @file GraphicCore.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCore__
#define __MugenEngine_GraphicCore__

#include <d3d12.h>
#include <dxgi1_6.h>

#include <wrl/client.h>

#include <vector>
#include <string>

#include "GraphicCommandList.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTex.lib")

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicDevice
		@brief		グラフィック制御部分の中核となるクラス
	*//***********************************************************************/
	class MEGraphicDevice
	{
	public:
		//! インスタンスの取得
		static MEGraphicDevice& GetIns();
		//! 最初に必ず呼ばれる初期化処理
		void Initialize(int window_width, int window_height);

	private:
		//! デフォルトコンストラクタ
		MEGraphicDevice();
		//!コピーコンストラクタ(削除)
		MEGraphicDevice(const MEGraphicDevice&) = delete;

		Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;			//!< DX12デバイス
		Microsoft::WRL::ComPtr<IDXGIFactory6> m_dxgiFactory = nullptr;		//!< DXGIデバイス

		GraphicCommandList m_graphicCommandList;							//!< コマンドリスト
	};
}

#endif//__MugenEngine_GraphicCore__