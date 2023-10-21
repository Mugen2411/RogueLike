//! @file StateMachine.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_StateMachine__
#define __MagicaRogue_StateMachine__

#include <unordered_map>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRStateMachine
		@brief		�X�e�[�g�}�V����\������N���X
	*//***********************************************************************/
	template<class T>
	class MRStateMachine
	{
	public:
		/**********************************************************************//**
			@brief			�X�V�֐���ǉ�����
			@param[in]		This					�֐������s������
			@return			�Ȃ�
		*//***********************************************************************/
		MRStateMachine(T* This):m_pThis(This){}

		/**********************************************************************//**
			@brief			�֐���ǉ�����
			@param[in]		ID					�X�e�[�g�ƑΉ�����ID
			@param[in]		updateFunc			�X�V�֐��|�C���^
			@param[in]		renderFunc			�`��֐��|�C���^
			@return			�Ȃ�
		*//***********************************************************************/
		void Register(int state, void (T::* updateFunc)(void), void (T::* renderFunc)(void)const) {
			m_updateList[state] = updateFunc;
			m_renderList[state] = renderFunc;
		}

		/**********************************************************************//**
			@brief			�X�V
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Update() 
		{
			(m_pThis->*(m_updateList[m_state]))();
		}

		/**********************************************************************//**
			@brief			�`��
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Render()const
		{
			(m_pThis->*(m_renderList.at(m_state)))();
		}

		/**********************************************************************//**
			@brief			�X�e�[�g�̑J��
			@param[in]			state			�J�ڐ�̃X�e�[�g
			@return			�Ȃ�
		*//***********************************************************************/
		void ChangeState(const int state) 
		{
			m_state = state;
		}
	private:
		int m_state;													//!< �X�e�[�g
		T* m_pThis;														//!< ���g�̃|�C���^
		std::unordered_map<int, void (T::*)(void)> m_updateList;
		std::unordered_map<int, void (T::*)(void)const> m_renderList;
	};
}

#endif//__MagicaRogue_StateMachine__