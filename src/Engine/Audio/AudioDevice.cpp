//! @file AudioDevice.cpp
//! @note Copyright (c) Mugen_GameLab

#include "AudioDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEAudioDevice::MEAudioDevice()
	{}

	/**********************************************************************//**
		@brief			デストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEAudioDevice::~MEAudioDevice()
	{
		m_pMasteringVoice->DestroyVoice();
	}

	/**********************************************************************//**
		@brief			初期化
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MEAudioDevice::Initialize()
	{
		XAudio2Create(m_device.ReleaseAndGetAddressOf());
		m_device->CreateMasteringVoice(&m_pMasteringVoice);
	}
}