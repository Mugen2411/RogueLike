//! @file MagicPoint.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MagicPoint__
#define __MagicaRogue_MagicPoint__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMagicPoint
		@brief		魔力を扱うクラス
	*//***********************************************************************/
	class MRMagicPoint
	{
	public:
		//! コンストラクタ
		MRMagicPoint(const float maximumValue);
		//! 回復
		void Heal(const float value);
		//! 割合回復
		void RatioHeal(const float ratio);
		//! ダメージ
		void Damage(const float value);
		//! 現在のHPを取得
		float GetValue()const {
			return m_value;
		}
		//! 現在のHPの割合を取得
		float GetRatio()const {
			return m_value / m_maximum;
		}
		//! 最大値を取得
		float GetMax()const {
			return m_maximum;
		}
	private:
		float m_value;									//!< 現在値
		float m_maximum;								//!< 最大値
	};
}

#endif//__MagicaRogue_MagicPoint__