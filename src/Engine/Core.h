//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"

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
		void Initialize(int window_width, int window_height);

		//! 描画結果を画面に反映させる
		void ScreenFlip();

	private:
		//! デフォルトコンストラクタ
		MECore();
		//!コピーコンストラクタ(削除)
		MECore(const MECore&) = delete;

		MEGraphicDevice m_graphicDevice;							//!< グラフィックデバイス
		MEGraphicCommandList m_graphicCommandList;					//!< グラフィックコマンドリスト
	};
}

#endif//__MugenEngine_Core__