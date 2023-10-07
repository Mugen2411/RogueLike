//! @file GraphicCore.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			デバイスとファクトリの初期化
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MEGraphicDevice::Initialize()
	{
		//DXGIファクトリ
		{
#ifdef _DEBUG
			_EnableDebugLayer();
			auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));
			if(FAILED(result))
			{
				OutputDebugStringA("DXGI Factory Initialize Error.\n");
		}
#else
			auto result = CreateDXGIFactory1(IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));
#endif
		}
		//DX12 アダプタ列挙
		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> adapters;
		Microsoft::WRL::ComPtr<IDXGIAdapter> tmpAdapter = nullptr;

		for(int i = 0; m_dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			adapters.push_back(tmpAdapter);
		}

		for(auto adpt : adapters)
		{
			DXGI_ADAPTER_DESC adesc = {};
			adpt->GetDesc(&adesc);

			std::wstring strDesc(adesc.Description);
			if(strDesc.find(L"NVIDIA") != std::string::npos)
			{
				tmpAdapter = adpt;
				break;
			}
		}

		//DX12 デバイス初期化
		D3D_FEATURE_LEVEL levels[] = {
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		D3D_FEATURE_LEVEL featureLevel;

		for(auto lv : levels)
		{
			if(D3D12CreateDevice(tmpAdapter.Get(), lv, IID_PPV_ARGS(m_device.ReleaseAndGetAddressOf())))
			{
				featureLevel = lv;
				break;
			}
		}
	}

	/**********************************************************************//**
		@brief			デバイスの生ポインタを取得
		@param			なし
		@return			デバイスの生ポインタ
	*//***********************************************************************/
	ID3D12Device * const MEGraphicDevice::GetDevice() const
	{
		return m_device.Get();
	}

	/**********************************************************************//**
		@brief			ファクトリの生ポインタを取得
		@param			なし
		@return			ファクトリの生ポインタ
	*//***********************************************************************/
	IDXGIFactory4* const MEGraphicDevice::GetFactory() const
	{
		return m_dxgiFactory.Get();
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEGraphicDevice::MEGraphicDevice()
	{}

	/**********************************************************************//**
		@brief			デバッグレイヤーの有効化
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MEGraphicDevice::_EnableDebugLayer()
	{
		ID3D12Debug* debugLayer = nullptr;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
		debugLayer->EnableDebugLayer();
		debugLayer->Release();

		Microsoft::WRL::ComPtr<ID3D12Debug> spDebugController0;
		Microsoft::WRL::ComPtr<ID3D12Debug1> spDebugController1;
		D3D12GetDebugInterface(IID_PPV_ARGS(&spDebugController0));
		spDebugController0->QueryInterface(IID_PPV_ARGS(&spDebugController1));
		spDebugController1->SetEnableGPUBasedValidation(true);
	}
}
