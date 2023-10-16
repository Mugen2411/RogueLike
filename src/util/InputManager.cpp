#include "InputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRInputManager::Update()
	{
		auto& keyManager = mugen_engine::MEKeyInputManager::GetIns();
		size_t numKey = m_pushedFrame.size();
		for (int i = 0; i < numKey; ++i)
		{
			if (keyManager.GetKey(i) & 0b11)
			{
				++m_pushedFrame[i];
			}
			else
			{
				m_pushedFrame[i] = 0;
			}
		}
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRInputManager::MRInputManager()
	{
		auto& keyManager = mugen_engine::MEKeyInputManager::GetIns();
		keyManager.AddKeycode(static_cast<char>(MRKeyCode::RIGHT), 'D',
			mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
		m_pushedFrame.push_back(0);
		keyManager.AddKeycode(static_cast<char>(MRKeyCode::DOWN), 'S',
			mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLD, XINPUT_GAMEPAD_DPAD_DOWN);
		m_pushedFrame.push_back(0);
		keyManager.AddKeycode(static_cast<char>(MRKeyCode::LEFT), 'A',
			mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLL, XINPUT_GAMEPAD_DPAD_LEFT);
		m_pushedFrame.push_back(0);
		keyManager.AddKeycode(static_cast<char>(MRKeyCode::UP), 'W',
			mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLU, XINPUT_GAMEPAD_DPAD_UP);
		m_pushedFrame.push_back(0);
	}
}