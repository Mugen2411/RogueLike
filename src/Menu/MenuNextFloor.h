//! @file MenuNextFloor.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MenuNextFloor__
#define __MagicaRogue_MenuNextFloor__

#include "MenuInterface.h"
#include "../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMenuNextFloor
		@brief		���̊K�w�֐i�݂܂����H���j���[
	*//***********************************************************************/
	class MRMenuNextFloor : public MRMenuInterface
	{
	public:
		//! �R���X�g���N�^
		MRMenuNextFloor(MREventQueue& eventQueue);
		//! �X�V
		int Update();
		//! �`��
		void Render() const;
	private:
		mugen_engine::MEImage* m_baseImg;			//!< ���j���[�̔w�i�摜
		mugen_engine::MEFontData* m_titleFont;		//!< ���o���̃t�H���g
	};
}

#endif//__MagicaRogue_MenuNextFloor__