//! @file EventQueue.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EventQueue.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MREventQueue::MREventQueue()
	{}

	/**********************************************************************//**
		@brief			プッシュ
		@param[in]		eventId				イベントID
		@param[in]		Option				追加で通知する値
		@return			なし
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, const int Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.i = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			プッシュ
		@param[in]		eventId				イベントID
		@param[in]		Option				追加で通知する値
		@return			なし
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, const float Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.f = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			プッシュ
		@param[in]		eventId				イベントID
		@param[in]		Option				追加で通知する値
		@return			なし
	*//***********************************************************************/
	void MREventQueue::Push(const EVENT_ID eventId, void* Option)
	{
		eventData tmp = {};
		tmp.evnetId = eventId;
		tmp.optionValue.p = Option;
		m_eventQueue.push(tmp);
	}

	/**********************************************************************//**
		@brief			先頭を取得
		@param			なし
		@return			イベントデータ
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
		@brief			ポップ
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREventQueue::Pop()
	{
		m_eventQueue.pop();
	}

	/**********************************************************************//**
		@brief			リセット
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREventQueue::Reset()
	{
		while (!m_eventQueue.empty())
		{
			m_eventQueue.pop();
		}
	}
}