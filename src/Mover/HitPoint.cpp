//! @file HitPoint.cpp
//! @note Copyright (c) Mugen_GameLab

#include "HitPoint.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		maximumValue				最大値
		@return			なし
	*//***********************************************************************/
	MRHitPoint::MRHitPoint(const float maximumValue): m_value(maximumValue), m_maximum(maximumValue)
	{}

	/**********************************************************************//**
		@brief			回復
		@param[in]		value					回復する値
		@return			なし
	*//***********************************************************************/
	void MRHitPoint::Heal(const float value)
	{
		m_value += value;
		if (m_maximum > m_value)
		{
			m_value = m_maximum;
		}
	}

	/**********************************************************************//**
		@brief			割合回復
		@param[in]		ratio					回復する割合(0.0f～1.0f)
		@return			なし
	*//***********************************************************************/
	void MRHitPoint::RatioHeal(const float ratio)
	{
		Heal(m_maximum * ratio);
	}
	void MRHitPoint::Damage(const float value)
	{
		m_value -= value;
		if (m_value < 0.0f)
		{
			m_value = 0.0f;
		}
	}
}