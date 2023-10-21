//! @file Animator.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Animator.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		step			���t���[�����Z����l
		@param[in]		maximum			�ő�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRAnimator::MRAnimator(float step, float maximum): m_current(0.0f), m_step(step), m_maximum(maximum)
	{
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRAnimator::Update()
	{
		m_current += m_step;
		if (m_current > m_maximum)
		{
			m_current -= m_maximum;
		}
	}

	/**********************************************************************//**
		@brief			���Z�b�g
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRAnimator::Reset()
	{
		m_current = 0.0f;
	}

	/**********************************************************************//**
		@brief			���ݒl���擾
		@param			�Ȃ�
		@return			���ݒl
	*//***********************************************************************/
	float MRAnimator::Get() const
	{
		return m_current;
	}
}