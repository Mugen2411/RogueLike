//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicCore.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MECore
		@brief		���f�B�A�T�|�[�g�G���W���̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MECore
	{
	public:
		//! �C���X�^���X�̎擾
		static MECore& GetIns();
		//! �ŏ��ɕK���Ă΂�鏉��������
		void Initialize(int window_width, int window_height);

	private:
		//! �f�t�H���g�R���X�g���N�^
		MECore();
		//!�R�s�[�R���X�g���N�^(�폜)
		MECore(const MECore&) = delete;
	};
}

#endif//__MugenEngine_Core__