//! @file MagicPoint.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MagicPoint.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		maximumValue				�ő�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRMagicPoint::MRMagicPoint(const float maximumValue) : m_value(maximumValue), m_maximum(maximumValue)
	{}

	/**********************************************************************//**
		@brief			��
		@param[in]		value					�񕜂���l
		@return			�Ȃ�
	*//***********************************************************************/
	void MRMagicPoint::Heal(const float value)
	{
		m_value += value;
		if (m_maximum > m_value)
		{
			m_value = m_maximum;
		}
	}

	/**********************************************************************//**
		@brief			������
		@param[in]		ratio					�񕜂��銄��(0.0f�`1.0f)
		@return			�Ȃ�
	*//***********************************************************************/
	void MRMagicPoint::RatioHeal(const float ratio)
	{
		Heal(m_maximum * ratio);
	}
	void MRMagicPoint::Damage(const float value)
	{
		m_value -= value;
		if (m_value < 0.0f)
		{
			m_value = 0.0f;
		}
	}
}