//! @file Slime.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Enemy_Slime__
#define __MagicaRogue_Enemy_Slime__

#include "../EnemyInterface.h"
#include "../../../Engine/Core.h"
#include "../../../Util/Animator.h"
#include "../../../Util/StateMachine.h"

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
		MRSlime(const float x, const float y, const constants::MRAttribute attribute,
			MRCamera *pCamera, MRMapData* pMapdata, const uint32_t seed);
		//! 更新
		MRAliveState Update();
		//! 描画
		void Render() const;
		//! 死んだとき
		void Dead();
		//! 消えたとき
		void Disappear();
	private:
		enum class STATE {
			STROLL,				//!< 徘徊
			CHASE,				//!< 追跡
			KNOCKBACKED			//!< ノックバック
		};

		//! 徘徊中の更新
		void _UpdateOnStroll();
		//! 徘徊中の描画
		void _RenderOnStroll() const;
		//! 追跡中の更新
		void _UpdateOnChase();
		//! 追跡中の描画
		void _RenderOnChase() const;

		mugen_engine::MEImage* m_img;						//!< 画像
		MRAnimator m_animator;								//!< アニメーター
		bool m_isLeft;										//!< 左を向いているか
		MRStateMachine<MRSlime> m_stateMachine;				//!< ステートマシン
	};
}

#endif//__MagicaRogue_Enemy_Slime__
