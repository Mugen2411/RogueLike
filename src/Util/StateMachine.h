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
		MRStateMachine(T* This):m_pThis(This), m_frameOnState(0){}

		/**********************************************************************//**
			@brief			�֐���ǉ�����
			@param[in]		state				�X�e�[�g
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
			(m_pThis->*(m_updateList[m_aliveState]))();
			++m_frameOnState;
		}

		/**********************************************************************//**
			@brief			�`��
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Render()const
		{
			(m_pThis->*(m_renderList.at(m_aliveState)))();
		}

		/**********************************************************************//**
			@brief			�X�e�[�g�̑J��
			@param[in]			state			�J�ڐ�̃X�e�[�g
			@return			�Ȃ�
		*//***********************************************************************/
		void ChangeState(const int state) 
		{
			m_frameOnState = 0;
			m_prevState = m_aliveState;
			m_aliveState = state;
		}

		/**********************************************************************//**
			@brief			�O�̃X�e�[�g�֖߂�
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void RestoreState()
		{
			int tmp = m_aliveState;
			m_aliveState = m_prevState;
			m_prevState = tmp;
		}
		/**********************************************************************//**
			@brief			�X�e�[�g�̎擾
			@param			�Ȃ�
			@return			�X�e�[�g
		*//***********************************************************************/
		int GetState() const
		{
			return m_aliveState;
		}

		/**********************************************************************//**
			@brief			�O�̃X�e�[�g�̎擾
			@param			�Ȃ�
			@return			�O�̃X�e�[�g
		*//***********************************************************************/
		int GetPrevState() const
		{
			return m_prevState;
		}

		/**********************************************************************//**
			@brief			�o�߃t���[���̎擾
			@param			�Ȃ�
			@return			�o�߃t���[��
		*//***********************************************************************/
		int GetFrame() const
		{
			return m_frameOnState;
		}
	private:
		int m_aliveState;												//!< �X�e�[�g
		int m_prevState;												//!< �O�̃X�e�[�g
		T* m_pThis;														//!< ���g�̃|�C���^
		int m_frameOnState;												//!< �X�e�[�g�̌o�߃t���[��
		std::unordered_map<int, void (T::*)(void)> m_updateList;		//!< �X�V�֐��̃��X�g
		std::unordered_map<int, void (T::*)(void)const> m_renderList;	//!< �`��֐��̃��X�g
	};
}

#endif//__MagicaRogue_StateMachine__