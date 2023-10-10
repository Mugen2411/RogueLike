//! @file AudioDevice.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_AudioDevice__
#define __MugenEngine_AudioDevice__

#include <xaudio2.h>
#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEAudioDevice
		@brief		�����T�|�[�g�̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MEAudioDevice
	{
	public:
		//! �R���X�g���N�^
		MEAudioDevice();
		//! �f�X�g���N�^
		~MEAudioDevice();
		//! ������
		void Initialize();
	private:
		Microsoft::WRL::ComPtr<IXAudio2> m_device;							//!< XAudio2�̒��j�ƂȂ�f�o�C�X
		IXAudio2MasteringVoice* m_pMasteringVoice;	//!< ���������ۂɏo�͂���ŏI�o�b�t�@
	};
}

#endif//__MugenEngine_AudioDevice__