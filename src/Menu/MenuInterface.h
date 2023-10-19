//! @file MenuInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MenuInterface__
#define __MagicaRogue_MenuInterface__

#include "../Util/EventQueue.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMenuInterface
		@brief		���C���V�[���Ŏg�����j���[���K���p������C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRMenuInterface
	{
	public:
		//! �R���X�g���N�^
		MRMenuInterface(MREventQueue& eventQueue):m_eventQueue(eventQueue){}
		//! �f�X�g���N�^
		virtual ~MRMenuInterface() {}
		//! �X�V
		virtual int Update() = 0;
		//! �`��
		virtual void Render() const = 0;

	protected:
		MREventQueue& m_eventQueue;					//!< �C�x���g�L���[
	};
}

#endif//__MagicaRogue_MenuInterface__