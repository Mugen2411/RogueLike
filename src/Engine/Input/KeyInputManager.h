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
		@brief		読み込んだフォントで画面上に文字列描画を行うクラス
	*//***********************************************************************/
	class MEKeyInputManager
	{
	public:
		/**********************************************************************//**
			@enum		GAMEPAD_KEYTYPE
			@brief		ゲームパッドの入力形式
		*//***********************************************************************/
		enum struct GAMEPAD_KEYTYPE : char {
			Buttons, LTrigger, RTrigger,
			ThumbLL, ThumbLR, ThumbLU, ThumbLD,
			ThumbRL, ThumbRR, ThumbRU, ThumbRD,
		};

		/**********************************************************************//**
			@brief			初期化
			@param			hWnd			メインウィンドウのハンドル
			@return			なし
		*//***********************************************************************/
		void Initialize(HWND hWnd);

		/**********************************************************************//**
			@brief			キーを監視対象に追加
			@param[in]		codeKey					ユーザー定義されたキーコード
			@param[in]		codeKeyboard			仮想キーコード
			@param[in]		typeGamepadKey			ゲームパッドの入力形式
			@param[in]		codeGamepad				ゲームパッドのボタンコード
			@return			なし
		*//***********************************************************************/
		bool AddKeycode(const char codeKey, const char codeKeyboard, const GAMEPAD_KEYTYPE typeGamepadKey, const short codeGamepad);

		/**********************************************************************//**
			@brief			更新
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Update();

		/**********************************************************************//**
			@brief			入力状況を取得
			@param[in]		codeKey					ユーザー定義されたキーコード
			@return			入力状況
		*//***********************************************************************/
		char GetKey(const char codeKey) const;

		/**********************************************************************//**
			@brief			インスタンスの取得
			@param			なし
			@return			インスタンス
		*//***********************************************************************/
		static MEKeyInputManager& GetIns(){
			static MEKeyInputManager instance;
			return instance;
		}
		
		/**********************************************************************//**
			@brief			マウスのX座標の取得
			@param			なし
			@return			マウスのX座標
		*//***********************************************************************/
		int GetMouseX() const
		{
			return m_currentMousePosX;
		}
		
		/**********************************************************************//**
			@brief			マウスのY座標の取得
			@param			なし
			@return			マウスのY座標
		*//***********************************************************************/
		int GetMouseY() const
		{
			return m_currentMousePosY;
		}
	private:
		/**********************************************************************//**
			@struct		KeyInf
			@brief		キーボードとパッドの入力を結び付ける構造体
		*//***********************************************************************/
		struct KeyInf {
			char state;
			char codeKey;
			char codeKeyboard;
			GAMEPAD_KEYTYPE typeGamepadKey;
			short codeGamepad;
		};

		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEKeyInputManager();

		/**********************************************************************//**
			@brief			マウス関連の入力を処理する
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _ProcessMouseInput();

		std::vector<char> m_statePrev;									//!< 前のフレームでの入力状況
		std::vector<KeyInf> m_watchingKeyInfos;							//!< 監視対象のキーコード
		const int m_cursorPosX;											//!< マウスを固定するX座標
		const int m_cursorPosY;											//!< マウスを固定するX座標
		HWND m_mainWindowHandle;										//!< メインウィンドウのハンドル
		int m_currentMousePosX;											//!< 現在のマウスのX座標
		int m_currentMousePosY;											//!< 現在のマウスのY座標
		float m_mouseSpeedRatio;										//!< マウスのスピード倍率
	};
}

#endif//__MugenEngine_KeyInputManager__