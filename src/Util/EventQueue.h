//! @file EventQueue.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EventQueue__
#define __MagicaRogue_EventQueue__

#include <queue>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MREventQueue
		@brief		発生したイベントを蓄えて処理を待つクラス
	*//***********************************************************************/
	class MREventQueue
	{
	public:
		enum class EVENT_ID {
			NONE, SELECT_GOTO_NEXT_FLOOR, GOTO_NEXT_FLOOR
		};
		struct eventData
		{
			EVENT_ID evnetId;
			union option
			{
				int i;
				float f;
				void* p;
			} optionValue;
		};
		//! コンストラクタ
		MREventQueue();
		//! プッシュ
		void Push(const EVENT_ID eventId, const int Option);
		//! プッシュ
		void Push(const EVENT_ID eventId, const float Option);
		//! プッシュ
		void Push(const EVENT_ID eventId, void* Option);
		//! 先頭を取得
		eventData GetTop() const;
		//! ポップ
		void Pop();
		//! リセット
		void Reset();
	private:
		std::queue<eventData> m_eventQueue;				//!< イベントデータを蓄えるキュー
	};
}

#endif//__MagicaRogue_EventQueue__