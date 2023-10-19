//! @file MenuNextFloor.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MenuNextFloor.h"
#include "../Util/Constants.h"
#include "../Util/InputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		eventQueue				�C�x���g�L���[
		@return			�Ȃ�
	*//***********************************************************************/
	MRMenuNextFloor::MRMenuNextFloor(MREventQueue& eventQueue) : MRMenuInterface(eventQueue), m_current(0)
	{
		m_baseImg = &mugen_engine::MECore::GetIns().GetGraph("menuBase");
		m_titleFont = &mugen_engine::MECore::GetIns().GetFont("menuTitle");
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	int MRMenuNextFloor::Update()
	{
		auto input = MRInputManager::GetIns();
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::DOWN) == 1)
		{
			m_current = (m_current + 1) % 2;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::UP) == 1)
		{
			m_current = (m_current + 1) % 2;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::MENU) == 1)
		{
			if (m_current == 0)m_eventQueue.Push(MREventQueue::EVENT_ID::GOTO_NEXT_FLOOR, 0);
			return 1;
		}
		return 0;
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRMenuNextFloor::Render() const
	{
		m_baseImg->DrawGraph2X(constants::screen::left_margin + constants::screen::width / 2,
			constants::screen::height / 2, constants::render_priority::MENU1_BASE);
		const float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_titleFont->DrawString(constants::screen::left_margin * 2 + 292, constants::screen::height - 90, color,
			constants::render_priority::MENU1_TEXT, L"���̊K�w�֐i�݂܂����H\n\n\n      �͂�\n      ������");
		m_titleFont->DrawString(constants::screen::left_margin * 2 + 292 + 36 * 2,
			constants::screen::height - 90 + 112 + 36 * m_current, color,
			constants::render_priority::MENU1_TEXT, L"��");
	}
}