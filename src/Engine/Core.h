//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicCore.h"

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
		//! 最初に必ず呼ばれる初期化処理
		void Initialize(int window_width, int window_height);

	private:
		//! デフォルトコンストラクタ
		MECore();
		//!コピーコンストラクタ(削除)
		MECore(const MECore&) = delete;
	};
}

#endif//__MugenEngine_Core__