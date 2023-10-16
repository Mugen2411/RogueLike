//! @file InputManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_InputManager__
#define __MagicaRogue_InputManager__

#include "../Engine/Input/KeyInputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRInputManager
		@brief		�L�[�ƃp�b�h�̓��͂������N���X
	*//***********************************************************************/
	class MRInputManager
	{
	public:
		enum class MRKeyCode : char 
		{
			RIGHT = 0, DOWN, LEFT, UP
		};
		static MRInputManager& GetIns() {
			static MRInputManager s_instance;
			return s_instance;
		}
		//! ���͏󋵂̍X�V
		void Update();
		//! �������t���[�����̎擾
		int GetPushedFrame(MRKeyCode code)
		{
			return m_pushedFrame[static_cast<char>(code)];
		}
	private:
		//! �R���X�g���N�^
		MRInputManager();

		std::vector<int> m_pushedFrame;								//!< �L�[�����������ꂽ�t���[����
	};
}

#endif//__MagicaRogue_InputManager__
