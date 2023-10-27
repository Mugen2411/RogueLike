//! @file KeyInputManager.cpp
//! @note Copyright (c) Mugen_GameLab
//! 
#include "KeyInputManager.h"
#include <WinUser.h>

namespace mugen_engine
{
	MEKeyInputManager::MEKeyInputManager() : m_cursorPosX(320), m_cursorPosY(180), m_mouseSpeedRatio(0.5f),
		m_currentMousePosX(m_cursorPosX), m_currentMousePosY(m_cursorPosY)
	{
	}

	void MEKeyInputManager::_ProcessMouseInput()
	{
		if (GetForegroundWindow() == m_mainWindowHandle)
		{
			while(0 < ShowCursor(false));
			POINT mouse = {};
			GetCursorPos(&mouse);
			ScreenToClient(m_mainWindowHandle, &mouse);
			POINT center = {};
			center.x = m_cursorPosX;
			center.y = m_cursorPosY;
			m_currentMousePosX += static_cast<int>(m_mouseSpeedRatio * (mouse.x - center.x));
			m_currentMousePosY += static_cast<int>(m_mouseSpeedRatio * (mouse.y - center.y));
			ClientToScreen(m_mainWindowHandle, &center);
			SetCursorPos(center.x, center.y);
		}
		else
		{
			while (0 > ShowCursor(true));
		}
	}

	void MEKeyInputManager::Initialize(HWND hWnd)
	{
		m_mainWindowHandle = hWnd;
		POINT center = {};
		center.x = m_cursorPosX;
		center.y = m_cursorPosY;
		ClientToScreen(m_mainWindowHandle, &center);
		SetCursorPos(center.x, center.y);
	}

	bool MEKeyInputManager::AddKeycode(const char codeKey, const char codeKeyboard,
		const GAMEPAD_KEYTYPE typeGamepadKey, const short codeGamepad)
	{
		KeyInf tmp = {};
		tmp.codeKey = codeKey;
		tmp.codeKeyboard = codeKeyboard;
		tmp.typeGamepadKey = typeGamepadKey;
		tmp.codeGamepad = codeGamepad;
		m_watchingKeyInfos.push_back(tmp);
		m_statePrev.push_back(0);
		return true;
	}
	void MEKeyInputManager::Update()
	{
		XINPUT_STATE stateXInp;
		DWORD dwRes = XInputGetState(0, &stateXInp);
		int numRegistered = static_cast<int>(m_watchingKeyInfos.size());
		for (int i = 0; i < numRegistered; ++i)
		{
			bool flagKB = GetAsyncKeyState(m_watchingKeyInfos[i].codeKeyboard) & 0x8000;
			bool flagXI = false;
			if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::Buttons)
				flagXI = stateXInp.Gamepad.wButtons & m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::LTrigger)
				flagXI = stateXInp.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::RTrigger)
				flagXI = stateXInp.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbLL)
				flagXI = stateXInp.Gamepad.sThumbLX < -m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbLR)
				flagXI = stateXInp.Gamepad.sThumbLX > m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbLU)
				flagXI = stateXInp.Gamepad.sThumbLY < -m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbLD)
				flagXI = stateXInp.Gamepad.sThumbLY > m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbRL)
				flagXI = stateXInp.Gamepad.sThumbRX < -m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbRR)
				flagXI = stateXInp.Gamepad.sThumbRX > m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbRU)
				flagXI = stateXInp.Gamepad.sThumbRY < -m_watchingKeyInfos[i].codeGamepad;
			else if (m_watchingKeyInfos[i].typeGamepadKey == GAMEPAD_KEYTYPE::ThumbRD)
				flagXI = stateXInp.Gamepad.sThumbRY > m_watchingKeyInfos[i].codeGamepad;
			if (dwRes != ERROR_SUCCESS)
				flagXI = false;
			if (flagKB || flagXI)
				m_watchingKeyInfos[i].state = ((m_statePrev[i] << 1) ^ 0b011) & 0b011;
			else
				m_watchingKeyInfos[i].state = (m_statePrev[i] << 2) & 0b100;
			m_statePrev[i] = m_watchingKeyInfos[i].state;

			_ProcessMouseInput();
		}
	}
	char MEKeyInputManager::GetKey(const char codeKey) const
	{
		int numRegistered = static_cast<int>(m_watchingKeyInfos.size());
		for (int i = 0; i < numRegistered; ++i)
		{
			if (m_watchingKeyInfos[i].codeKey == codeKey)
				return m_watchingKeyInfos[i].state;
		}
		return 0;
	}
}