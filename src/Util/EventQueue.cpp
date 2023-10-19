//! @file EventQueue.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EventQueue.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MREventQueue::MREventQueue()
	{}

	/**********************************************************************//**
		@brief			�v�b�V��
		@param[in]		eventId				�C�x���gID
		@param[in]		Option				�ǉ��Œʒm����l
		@return			�Ȃ�
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, const int Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.i = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			�v�b�V��
		@param[in]		eventId				�C�x���gID
		@param[in]		Option				�ǉ��Œʒm����l
		@return			�Ȃ�
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, const float Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.f = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			�v�b�V��
		@param[in]		eventId				�C�x���gID
		@param[in]		Option				�ǉ��Œʒm����l
		@return			�Ȃ�
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, void* Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.p = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			�擪���擾
		@param			�Ȃ�
		@return			�C�x���g�f�[�^
	*//***********************************************************************/
	MREventQueue::eventData MREventQueue::GetTop() const
	{	
		if (m_eventQueue.empty())
		{
			return eventData{ EVENT_ID::NONE, 0 };
		}
		return m_eventQueue.front();
	}

	/**********************************************************************//**
		@brief			�|�b�v
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MREventQueue::Pop()
	{
		m_eventQueue.pop();
	}

	/**********************************************************************//**
		@brief			���Z�b�g
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MREventQueue::Reset()
	{
		while (!m_eventQueue.empty())
		{
			m_eventQueue.pop();
		}
	}
}