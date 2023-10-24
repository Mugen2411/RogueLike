//! @file KeyInputManager.h
//! @note Copyright (c) Mugen_GameLab
//! 
//! arreanged from https://qiita.com/Tengu712/items/2da15de879676d8631f9

#ifndef __MugenEngine_KeyInputManager__
#define __MugenEngine_KeyInputManager__

#include <Windows.h>
#include <Xinput.h>
#include <WinUser.h>
#include <vector>

#pragma comment(lib, "Xinput.lib")

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEKeyInputManager
		@brief		�ǂݍ��񂾃t�H���g�ŉ�ʏ�ɕ�����`����s���N���X
	*//***********************************************************************/
	class MEKeyInputManager
	{
	public:
		enum struct GAMEPAD_KEYTYPE : char {
			Buttons, LTrigger, RTrigger,
			ThumbLL, ThumbLR, ThumbLU, ThumbLD,
			ThumbRL, ThumbRR, ThumbRU, ThumbRD,
		};
		//! ������
		void Initialize(HWND hWnd);
		//! �L�[�R�[�h���Ď��Ώۂɒǉ�
		bool AddKeycode(char codeKey, char codeKeyboard, GAMEPAD_KEYTYPE typeGamepadKey, short codeGamepad);
		//! ���͏󋵂��X�V
		void Update();
		//! ���͏󋵂��擾
		char GetKey(char codeKey);
		//! �C���X�^���X�̎擾
		static MEKeyInputManager& GetIns(){
			static MEKeyInputManager instance;
			return instance;
		}
	private:
		/**********************************************************************//**
			@struct		KeyInf
			@brief		�L�[�{�[�h�ƃp�b�h�̓��͂����ѕt����\����
		*//***********************************************************************/
		struct KeyInf {
			char state;
			char codeKey;
			char codeKeyboard;
			GAMEPAD_KEYTYPE typeGamepadKey;
			short codeGamepad;
		};

		//! �R���X�g���N�^
		MEKeyInputManager();
		//! �}�E�X��^�񒆂ɌŒ�
		void _SetMousePosition();

		std::vector<char> m_statePrev;									//!< �O�̃t���[���ł̓��͏�
		std::vector<KeyInf> m_watchingKeyInfos;							//!< �Ď��Ώۂ̃L�[�R�[�h
		const int m_cursorPosX;											//!< �}�E�X���Œ肷��X���W
		const int m_cursorPosY;											//!< �}�E�X���Œ肷��X���W
		HWND m_mainWindowHandle;										//!< ���C���E�B���h�E�̃n���h��
	};
}

#endif//__MugenEngine_KeyInputManager__