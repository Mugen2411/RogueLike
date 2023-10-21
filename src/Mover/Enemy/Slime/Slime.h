//! @file Slime.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Enemy_Slime__
#define __MagicaRogue_Enemy_Slime__

#include "../EnemyInterface.h"
#include "../../../Engine/Core.h"
#include "../../../Util/Animator.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSlime
		@brief		敵「スライム」を表現するクラス
	*//***********************************************************************/
	class MRSlime : public MREnemyInterface
	{
	public:
		//! コンストラクタ
		MRSlime(const float x, const float y, const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata);
		//! 更新
		MRAliveState Update();
		//! 描画
		void Render() const;
		//! 死んだとき
		void Dead();
		//! 消えたとき
		void Disappear();
	private:
		mugen_engine::MEImage* m_img;				//!< 画像
		MRAnimator m_animator;						//!< アニメーター
		bool m_isLeft;								//!< 左を向いているか
	};
}

#endif//__MagicaRogue_Enemy_Slime__
