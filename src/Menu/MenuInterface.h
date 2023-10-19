//! @file MenuInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MenuInterface__
#define __MagicaRogue_MenuInterface__

#include "../Util/EventQueue.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMenuInterface
		@brief		メインシーンで使うメニューが必ず継承するインターフェース
	*//***********************************************************************/
	class MRMenuInterface
	{
	public:
		//! コンストラクタ
		MRMenuInterface(MREventQueue& eventQueue):m_eventQueue(eventQueue){}
		//! デストラクタ
		virtual ~MRMenuInterface() {}
		//! 更新
		virtual int Update() = 0;
		//! 描画
		virtual void Render() const = 0;

	protected:
		MREventQueue& m_eventQueue;					//!< イベントキュー
	};
}

#endif//__MagicaRogue_MenuInterface__