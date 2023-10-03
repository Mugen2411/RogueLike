//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"
#include "Graphic/GraphicRenderTarget.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MECore
		@brief		メディアサポートエンジンの中核となるクラス
	*//***********************************************************************/
	class MECore
	{
	public:
		//! インスタンスの取得
		static MECore& GetIns();
		//! 最初に必ず呼び出す初期化処理
		void Initialize(const std::wstring window_title, int window_width, int window_height);
		//! 最後に必ず呼び出す終了処理
		void Finalize();
		//! システムのメッセージを処理する
		int ProcessMessage();
		//! 描画結果を画面に反映させる
		void ScreenFlip();

	private:
		//! デフォルトコンストラクタ
		MECore();
		//! コピーコンストラクタ(削除)
		MECore(const MECore&) = delete;

		//! ウィンドウの作成
		void _CreateWindow();
		
		HWND m_windowHandle;										//!< ウィンドウハンドル
		std::wstring m_windowTitle;									//!< ウィンドウの名前(ウィンドウクラスの名前)
		WNDCLASSEX m_windowClass;									//!< ウィンドウクラス
		int m_windowWidth;											//!< ウィンドウの横幅
		int m_windowHeight;											//!< ウィンドウの高さ

		MEGraphicDevice m_graphicDevice;							//!< グラフィックデバイス
		MEGraphicCommandList m_graphicCommandList;					//!< グラフィックコマンドリスト
		MEGraphicRenderTarget m_renderTarget;						//!< レンダーターゲット
	};
}

#endif//__MugenEngine_Core__