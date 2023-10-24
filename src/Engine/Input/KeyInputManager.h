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
		enum struct GAMEPAD_KEYTYPE : char {
			Buttons, LTrigger, RTrigger,
			ThumbLL, ThumbLR, ThumbLU, ThumbLD,
			ThumbRL, ThumbRR, ThumbRU, ThumbRD,
		};
		//! 初期化
		void Initialize(HWND hWnd);
		//! キーコードを監視対象に追加
		bool AddKeycode(char codeKey, char codeKeyboard, GAMEPAD_KEYTYPE typeGamepadKey, short codeGamepad);
		//! 入力状況を更新
		void Update();
		//! 入力状況を取得
		char GetKey(char codeKey);
		//! インスタンスの取得
		static MEKeyInputManager& GetIns(){
			static MEKeyInputManager instance;
			return instance;
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

		//! コンストラクタ
		MEKeyInputManager();
		//! マウスを真ん中に固定
		void _SetMousePosition();

		std::vector<char> m_statePrev;									//!< 前のフレームでの入力状況
		std::vector<KeyInf> m_watchingKeyInfos;							//!< 監視対象のキーコード
		const int m_cursorPosX;											//!< マウスを固定するX座標
		const int m_cursorPosY;											//!< マウスを固定するX座標
		HWND m_mainWindowHandle;										//!< メインウィンドウのハンドル
	};
}

#endif//__MugenEngine_KeyInputManager__