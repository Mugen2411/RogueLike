//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Graphic_Core__
#define __MugenEngine_Graphic_Core__

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicCore
		@brief		グラフィック制御部分の中核となるクラス
	*//***********************************************************************/
	class MEGraphicCore
	{
	public:
		//! デフォルトコンストラクタ
		MEGraphicCore();
		//!コピーコンストラクタ(削除)
		MEGraphicCore(const MEGraphicCore&) = delete;
		//! 最初に必ず呼ばれる初期化処理
		void Initialize(int window_width, int window_height);

	private:

	};
}

#endif//__MugenEngine_Graphic_Core__