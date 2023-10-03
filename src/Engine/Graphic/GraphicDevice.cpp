//! @file GraphicCore.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			������
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�C���X�^���X
	*//***********************************************************************/
	void MEGraphicDevice::Initialize(const int window_width, const int window_height)
	{
		//DXGI�t�@�N�g��
		{
#ifdef _DEBUG
			auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));
#else
			auto result = CreateDXGIFactory1(IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()));
#endif
		}
		//DX12 �A�_�v�^��
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

		//DX12 �f�o�C�X������
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

	ID3D12Device * const MEGraphicDevice::GetDevice() const
	{
		return m_device.Get();
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicDevice::MEGraphicDevice()
	{}
}
