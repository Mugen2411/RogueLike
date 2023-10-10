//! @file AudioDevice.cpp
//! @note Copyright (c) Mugen_GameLab

#include "AudioDevice.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEAudioDevice::MEAudioDevice()
	{}

	/**********************************************************************//**
		@brief			�f�X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEAudioDevice::~MEAudioDevice()
	{
		m_pMasteringVoice->DestroyVoice();
	}

	/**********************************************************************//**
		@brief			������
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEAudioDevice::Initialize()
	{
		XAudio2Create(m_device.ReleaseAndGetAddressOf());
		m_device->CreateMasteringVoice(&m_pMasteringVoice);
	}
}