//! @file GraphicDevice.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicDevice__
#define __MugenEngine_GraphicDevice__

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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicDevice();

		//!コピーコンストラクタ(削除)
		MEGraphicDevice(const MEGraphicDevice&) = delete;

		/**********************************************************************//**
			@brief			デバイスとファクトリの初期化
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Initialize();

		/**********************************************************************//**
			@brief			デバイスの生ポインタを取得
			@param			なし
			@return			デバイスの生ポインタ
		*//***********************************************************************/
		ID3D12Device* const GetDevice() const
		{
			return m_device.Get();
		}

		/**********************************************************************//**
			@brief			ファクトリの生ポインタを取得
			@param			なし
			@return			ファクトリの生ポインタ
		*//***********************************************************************/
		IDXGIFactory4* const GetFactory() const
		{
			return m_dxgiFactory.Get();
		}

	private:
		/**********************************************************************//**
			@brief			デバッグレイヤーの有効化
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _EnableDebugLayer();

		Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;			//!< DX12デバイス
		Microsoft::WRL::ComPtr<IDXGIFactory6> m_dxgiFactory = nullptr;		//!< DXGIデバイス
	};
}

#endif//__MugenEngine_GraphicDevice__