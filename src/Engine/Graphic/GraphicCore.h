//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Graphic_Core__
#define __MugenEngine_Graphic_Core__

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicCore
		@brief		�O���t�B�b�N���䕔���̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MEGraphicCore
	{
	public:
		//! �f�t�H���g�R���X�g���N�^
		MEGraphicCore();
		//!�R�s�[�R���X�g���N�^(�폜)
		MEGraphicCore(const MEGraphicCore&) = delete;
		//! �ŏ��ɕK���Ă΂�鏉��������
		void Initialize(int window_width, int window_height);

	private:

	};
}

#endif//__MugenEngine_Graphic_Core__