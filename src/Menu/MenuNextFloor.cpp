//! @file MenuNextFloor.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MenuNextFloor.h"
#include "../Util/Constants.h"
#include "../Util/InputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		eventQueue				イベントキュー
		@return			なし
	*//***********************************************************************/
	MRMenuNextFloor::MRMenuNextFloor(MREventQueue& eventQueue) : MRMenuInterface(eventQueue)
	{
		m_baseImg = &mugen_engine::MECore::GetIns().GetGraph("menuBase");
		m_titleFont = &mugen_engine::MECore::GetIns().GetFont("menuTitle");
	}

	/**********************************************************************//**
		@brief			更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	int MRMenuNextFloor::Update()
	{
		auto input = MRInputManager::GetIns();
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::MENU) == 1)
		{
			m_eventQueue.Push(MREventQueue::EVENT_ID::GOTO_NEXT_FLOOR, 0);
			return 1;
		}
		return 0;
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRMenuNextFloor::Render() const
	{
		m_baseImg->DrawGraph2X(constants::screen::left_margin + constants::screen::width / 2,
			constants::screen::height / 2, constants::render_priority::MENU1_BASE);
		const float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_titleFont->DrawString(constants::screen::left_margin * 2 + 292, constants::screen::height - 90, color,
			constants::render_priority::MENU1_TEXT, L"次の階層へ進みますか？\n\n\n      →はい");
	}
}