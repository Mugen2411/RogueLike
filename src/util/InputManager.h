//! @file InputManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_InputManager__
#define __MagicaRogue_InputManager__

#include "../Engine/Input/KeyInputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRInputManager
		@brief		キーとパッドの入力を扱うクラス
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
		//! 入力状況の更新
		void Update();
		//! 長押しフレーム数の取得
		int GetPushedFrame(MRKeyCode code)
		{
			return m_pushedFrame[static_cast<char>(code)];
		}
	private:
		//! コンストラクタ
		MRInputManager();

		std::vector<int> m_pushedFrame;								//!< キーが長押しされたフレーム数
	};
}

#endif//__MagicaRogue_InputManager__
