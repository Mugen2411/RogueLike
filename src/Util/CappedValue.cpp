//! @file CappedValue.cpp
//! @note Copyright (c) Mugen_GameLab

#include "CappedValue.h"
#include <algorithm>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		initialValue					初期値
		@param[in]		minimumValue					最小値
		@param[in]		maximumValue					最大値
		@return			なし
	*//***********************************************************************/
	MRCappedValue::MRCappedValue(const float initialValue, const float minimumValue, const float maximumValue):
		m_value(initialValue), m_minimum(minimumValue), m_maximum(maximumValue)
	{}

	/**********************************************************************//**
		@brief			値を取得
		@param			なし
		@return			現在の値
	*//***********************************************************************/
	float MRCappedValue::GetValue() const
	{
		return m_value;
	}

	/**********************************************************************//**
		@brief			加算
		@param[in]		value					加算する値
		@return			加算された後の値
	*//***********************************************************************/
	float MRCappedValue::Add(const float value)
	{
		m_value = std::clamp(m_value + value, m_minimum, m_maximum);
		return m_value;
	}

	/**********************************************************************//**
		@brief			最小値かどうか
		@param			なし
		@return			最小値ならtrue
	*//***********************************************************************/
	bool MRCappedValue::isMinimum() const
	{
		return m_value == m_minimum;
	}

	/**********************************************************************//**
		@brief			最大値かどうか
		@param			なし
		@return			最大値ならtrue
	*//***********************************************************************/
	bool MRCappedValue::isMaximum() const
	{
		return m_value == m_maximum;
	}

	/**********************************************************************//**
		@brief			割合を取得
		@param			なし
		@return			最大値と最小値を基にした割合
	*//***********************************************************************/
	float MRCappedValue::GetRatio() const
	{
		return (m_value - m_minimum) / (m_maximum - m_minimum);
	}
}