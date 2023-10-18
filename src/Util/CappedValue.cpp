//! @file CappedValue.cpp
//! @note Copyright (c) Mugen_GameLab

#include "CappedValue.h"
#include <algorithm>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		initialValue					�����l
		@param[in]		minimumValue					�ŏ��l
		@param[in]		maximumValue					�ő�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRCappedValue::MRCappedValue(const float initialValue, const float minimumValue, const float maximumValue):
		m_value(initialValue), m_minimum(minimumValue), m_maximum(maximumValue)
	{}

	/**********************************************************************//**
		@brief			�l���擾
		@param			�Ȃ�
		@return			���݂̒l
	*//***********************************************************************/
	float MRCappedValue::GetValue() const
	{
		return m_value;
	}

	/**********************************************************************//**
		@brief			���Z
		@param[in]		value					���Z����l
		@return			���Z���ꂽ��̒l
	*//***********************************************************************/
	float MRCappedValue::Add(const float value)
	{
		m_value = std::clamp(m_value + value, m_minimum, m_maximum);
		return m_value;
	}

	/**********************************************************************//**
		@brief			�ŏ��l���ǂ���
		@param			�Ȃ�
		@return			�ŏ��l�Ȃ�true
	*//***********************************************************************/
	bool MRCappedValue::isMinimum() const
	{
		return m_value == m_minimum;
	}

	/**********************************************************************//**
		@brief			�ő�l���ǂ���
		@param			�Ȃ�
		@return			�ő�l�Ȃ�true
	*//***********************************************************************/
	bool MRCappedValue::isMaximum() const
	{
		return m_value == m_maximum;
	}

	/**********************************************************************//**
		@brief			�������擾
		@param			�Ȃ�
		@return			�ő�l�ƍŏ��l����ɂ�������
	*//***********************************************************************/
	float MRCappedValue::GetRatio() const
	{
		return (m_value - m_minimum) / (m_maximum - m_minimum);
	}
}