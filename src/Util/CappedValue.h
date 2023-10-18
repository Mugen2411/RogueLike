//! @file CappedValue.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_CappedValue__
#define __MagicaRogue_CappedValue__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRCappedValue
		@brief		最大値と最小値が決まっている数値を扱うクラス
	*//***********************************************************************/
	class MRCappedValue
	{
	public:
		//! コンストラクタ
		MRCappedValue(const float initialValue, const float minimumValue, const float maximumValue);
		//! 値を取得
		float GetValue() const;
		//! 加算
		float Add(const float value);
		//! 最小値かどうか
		bool isMinimum() const;
		//! 最大値かどうか
		bool isMaximum() const;
		//! 割合を取得
		float GetRatio() const;
	private:
		float m_value;							//!< 現在値
		float m_minimum;						//!< 最小値
		float m_maximum;						//!< 最大値
	};
}

#endif//__MagicaRogue_CappedValue__