//! @file EventQueue.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EventQueue__
#define __MagicaRogue_EventQueue__

#include <queue>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MREventQueue
		@brief		���������C�x���g��~���ď�����҂N���X
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
		//! �R���X�g���N�^
		MREventQueue();
		//! �v�b�V��
		void Push(const EVENT_ID eventId, const int Option);
		//! �v�b�V��
		void Push(const EVENT_ID eventId, const float Option);
		//! �v�b�V��
		void Push(const EVENT_ID eventId, void* Option);
		//! �擪���擾
		eventData GetTop() const;
		//! �|�b�v
		void Pop();
		//! ���Z�b�g
		void Reset();
	private:
		std::queue<eventData> m_eventQueue;				//!< �C�x���g�f�[�^��~����L���[
	};
}

#endif//__MagicaRogue_EventQueue__