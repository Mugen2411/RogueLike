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
		@brief		音声サポートの中核となるクラス
	*//***********************************************************************/
	class MEAudioDevice
	{
	public:
		//! コンストラクタ
		MEAudioDevice();
		//! デストラクタ
		~MEAudioDevice();
		//! 初期化
		void Initialize();
	private:
		Microsoft::WRL::ComPtr<IXAudio2> m_device;							//!< XAudio2の中核となるデバイス
		IXAudio2MasteringVoice* m_pMasteringVoice;	//!< 音声を実際に出力する最終バッファ
	};
}

#endif//__MugenEngine_AudioDevice__