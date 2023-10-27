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
		@brief		�O���t�B�b�N���䕔���̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MEGraphicDevice
	{
	public:
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEGraphicDevice();

		//!�R�s�[�R���X�g���N�^(�폜)
		MEGraphicDevice(const MEGraphicDevice&) = delete;

		/**********************************************************************//**
			@brief			�f�o�C�X�ƃt�@�N�g���̏�����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Initialize();

		/**********************************************************************//**
			@brief			�f�o�C�X�̐��|�C���^���擾
			@param			�Ȃ�
			@return			�f�o�C�X�̐��|�C���^
		*//***********************************************************************/
		ID3D12Device* const GetDevice() const
		{
			return m_device.Get();
		}

		/**********************************************************************//**
			@brief			�t�@�N�g���̐��|�C���^���擾
			@param			�Ȃ�
			@return			�t�@�N�g���̐��|�C���^
		*//***********************************************************************/
		IDXGIFactory4* const GetFactory() const
		{
			return m_dxgiFactory.Get();
		}

	private:
		/**********************************************************************//**
			@brief			�f�o�b�O���C���[�̗L����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _EnableDebugLayer();

		Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;			//!< DX12�f�o�C�X
		Microsoft::WRL::ComPtr<IDXGIFactory6> m_dxgiFactory = nullptr;		//!< DXGI�f�o�C�X
	};
}

#endif//__MugenEngine_GraphicDevice__