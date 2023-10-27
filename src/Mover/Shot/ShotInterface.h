//! @file ShotInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_ShotInterface__
#define __MagicaRogue_ShotInterface__

#include "../MoverInterface.h"
#include "../../Util/Constants.h"

namespace magica_rogue
{
	class MREnemyInterface;
	/**********************************************************************//**
		@class		MRShotInterface
		@brief		自機ショットが必ず継承するインターフェース
	*//***********************************************************************/
	class MRShotInterface : MRMoverInterface
	{
	public:
		//! コンストラクタ
		MRShotInterface(const float x, const float y, const float vx, const float vy, const float size,
			const float attack, const constants::MRAttribute attribute, int duration);
		//! 更新
		virtual MRAliveState Update() = 0;
		//! 描画
		void Render() const = 0;
		//! 敵との当たり判定
		void HitWithEnemy(MREnemyInterface& enemy);
	private:
		const float m_attack;								//!< 攻撃力
		const constants::MRAttribute m_attribute;			//!< 属性
		int m_frame;										//!< 生成されてからのフレーム数
		const int m_duration;									//!< 消えるまでの時間
	};
}

#endif//__MagicaRogue_ShotInterface__