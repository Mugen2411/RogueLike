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
		@brief		���C���V�[���Ŏg�����j���[���Ǘ�����N���X
	*//***********************************************************************/
	class MRMenuManager
	{
	public:
		//! �R���X�g���N�^
		MRMenuManager(MREventQueue& eventQueue):m_eventQueue(eventQueue)
		{
			mugen_engine::MECore::GetIns().LoadGraph("menuBase", L"media/graphic/UI/menuBase.png");
			mugen_engine::MECore::GetIns().LoadFont("menuTitle", L"�l�r �S�V�b�N", 36);
		}

		//! �f�X�g���N�^
		virtual ~MRMenuManager() {}

		//! ���j���[���v�b�V������
		void Push(std::unique_ptr<MRMenuInterface>&& menu)
		{
			if (!m_menu)
			{
				m_menu = (std::move(menu));
			}
		}

		//! �X�V
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

		//! �`��
		void Render() const
		{
			if (m_menu)
			{
				m_menu->Render();
			}
		}
	protected:
		MREventQueue& m_eventQueue;					//!< �C�x���g�L���[
		std::unique_ptr<MRMenuInterface> m_menu;	//!< ���j���[�{��
	};
}

#endif//__MagicaRogue_MenuManager__