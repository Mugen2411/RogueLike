//! @file AudioDevice.cpp
//! @note Copyright (c) Mugen_GameLab

#include "AudioDevice.h"

namespace mugen_engine
{
	MEAudioDevice::MEAudioDevice()
	{}

	MEAudioDevice::~MEAudioDevice()
	{
		m_pMasteringVoice->DestroyVoice();
	}

	void MEAudioDevice::Initialize()
	{
		XAudio2Create(m_device.ReleaseAndGetAddressOf());
		m_device->CreateMasteringVoice(&m_pMasteringVoice);
	}
}