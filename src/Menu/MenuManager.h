//! @file MenuManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MenuManager__
#define __MagicaRogue_MenuManager__

#include "MenuInterface.h"
#include "../Util/EventQueue.h"
#include "../Engine/Core.h"
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMenuManager
		@brief		メインシーンで使うメニューを管理するクラス
	*//***********************************************************************/
	class MRMenuManager
	{
	public:
		//! コンストラクタ
		MRMenuManager(MREventQueue& eventQueue):m_eventQueue(eventQueue)
		{
			mugen_engine::MECore::GetIns().LoadGraph("menuBase", L"media/graphic/UI/menuBase.png");
			mugen_engine::MECore::GetIns().LoadFont("menuTitle", L"ＭＳ ゴシック", 36);
		}

		//! デストラクタ
		virtual ~MRMenuManager() {}

		//! メニューをプッシュする
		void Push(std::unique_ptr<MRMenuInterface>&& menu)
		{
			if (!m_menu)
			{
				m_menu = (std::move(menu));
			}
		}

		//! 更新
		bool Update()
		{
			if (m_menu)
			{
				int ret = m_menu->Update();
				if (ret != 0) m_menu.release();
				return true;
			}
			return false;
		}

		//! 描画
		void Render() const
		{
			if (m_menu)
			{
				m_menu->Render();
			}
		}
	protected:
		MREventQueue& m_eventQueue;					//!< イベントキュー
		std::unique_ptr<MRMenuInterface> m_menu;	//!< メニュー本体
	};
}

#endif//__MagicaRogue_MenuManager__