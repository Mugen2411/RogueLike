//! @file Animator.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Animator.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		step			毎フレーム加算する値
		@param[in]		maximum			最大値
		@return			なし
	*//***********************************************************************/
	MRAnimator::MRAnimator(float step, float maximum): m_current(0.0f), m_step(step), m_maximum(maximum)
	{
	}

	/**********************************************************************//**
		@brief			更新
		@param			なし
		@return			なし
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
		@brief			リセット
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRAnimator::Reset()
	{
		m_current = 0.0f;
	}

	/**********************************************************************//**
		@brief			現在値を取得
		@param			なし
		@return			現在値
	*//***********************************************************************/
	float MRAnimator::Get() const
	{
		return m_current;
	}
}