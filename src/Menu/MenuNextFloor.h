//! @file MenuNextFloor.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MenuNextFloor__
#define __MagicaRogue_MenuNextFloor__

#include "MenuInterface.h"
#include "../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMenuNextFloor
		@brief		次の階層へ進みますか？メニュー
	*//***********************************************************************/
	class MRMenuNextFloor : public MRMenuInterface
	{
	public:
		//! コンストラクタ
		MRMenuNextFloor(MREventQueue& eventQueue);
		//! 更新
		int Update();
		//! 描画
		void Render() const;
	private:
		mugen_engine::MEImage* m_baseImg;			//!< メニューの背景画像
		mugen_engine::MEFontData* m_titleFont;		//!< 見出しのフォント
	};
}

#endif//__MagicaRogue_MenuNextFloor__