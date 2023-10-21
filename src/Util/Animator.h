//! @file Animator.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Animator__
#define __MagicaRogue_Animator__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRAnimator
		@brief		アニメーションを管理するクラス
	*//***********************************************************************/
	class MRAnimator
	{
	public:
		//! コンストラクタ
		MRAnimator(float step, float maximum);
		//! 更新
		void Update();
		//! リセット
		void Reset();
		//! 現在値を取得
		float Get() const;
	private:
		float m_current;					//!< 現在値
		float m_maximum;					//!< 最大値
		float m_step;						//!< 毎フレーム加算する値
	};
}

#endif//__MagicaRogue_Animator__