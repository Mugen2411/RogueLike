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
		/**********************************************************************//**
			@enum		GAMEPAD_KEYTYPE
			@brief		�Q�[���p�b�h�̓��͌`��
		*//***********************************************************************/
		enum struct GAMEPAD_KEYTYPE : char {
			Buttons, LTrigger, RTrigger,
			ThumbLL, ThumbLR, ThumbLU, ThumbLD,
			ThumbRL, ThumbRR, ThumbRU, ThumbRD,
		};

		/**********************************************************************//**
			@brief			������
			@param			hWnd			���C���E�B���h�E�̃n���h��
			@return			�Ȃ�
		*//***********************************************************************/
		void Initialize(HWND hWnd);

		/**********************************************************************//**
			@brief			�L�[���Ď��Ώۂɒǉ�
			@param[in]		codeKey					���[�U�[��`���ꂽ�L�[�R�[�h
			@param[in]		codeKeyboard			���z�L�[�R�[�h
			@param[in]		typeGamepadKey			�Q�[���p�b�h�̓��͌`��
			@param[in]		codeGamepad				�Q�[���p�b�h�̃{�^���R�[�h
			@return			�Ȃ�
		*//***********************************************************************/
		bool AddKeycode(const char codeKey, const char codeKeyboard, const GAMEPAD_KEYTYPE typeGamepadKey, const short codeGamepad);

		/**********************************************************************//**
			@brief			�X�V
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Update();

		/**********************************************************************//**
			@brief			���͏󋵂��擾
			@param[in]		codeKey					���[�U�[��`���ꂽ�L�[�R�[�h
			@return			���͏�
		*//***********************************************************************/
		char GetKey(const char codeKey) const;

		/**********************************************************************//**
			@brief			�C���X�^���X�̎擾
			@param			�Ȃ�
			@return			�C���X�^���X
		*//***********************************************************************/
		static MEKeyInputManager& GetIns(){
			static MEKeyInputManager instance;
			return instance;
		}
		
		/**********************************************************************//**
			@brief			�}�E�X��X���W�̎擾
			@param			�Ȃ�
			@return			�}�E�X��X���W
		*//***********************************************************************/
		int GetMouseX() const
		{
			return m_currentMousePosX;
		}
		
		/**********************************************************************//**
			@brief			�}�E�X��Y���W�̎擾
			@param			�Ȃ�
			@return			�}�E�X��Y���W
		*//***********************************************************************/
		int GetMouseY() const
		{
			return m_currentMousePosY;
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

		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEKeyInputManager();

		/**********************************************************************//**
			@brief			�}�E�X�֘A�̓��͂���������
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _ProcessMouseInput();

		std::vector<char> m_statePrev;									//!< �O�̃t���[���ł̓��͏�
		std::vector<KeyInf> m_watchingKeyInfos;							//!< �Ď��Ώۂ̃L�[�R�[�h
		const int m_cursorPosX;											//!< �}�E�X���Œ肷��X���W
		const int m_cursorPosY;											//!< �}�E�X���Œ肷��X���W
		HWND m_mainWindowHandle;										//!< ���C���E�B���h�E�̃n���h��
		int m_currentMousePosX;											//!< ���݂̃}�E�X��X���W
		int m_currentMousePosY;											//!< ���݂̃}�E�X��Y���W
		float m_mouseSpeedRatio;										//!< �}�E�X�̃X�s�[�h�{��
	};
}

#endif//__MugenEngine_KeyInputManager__