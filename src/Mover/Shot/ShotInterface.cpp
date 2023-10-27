//! @file ShotInterface.cpp
//! @note Copyright (c) Mugen_GameLab

#include "ShotInterface.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]			x					X座標
		@param[in]			y					Y座標
		@param[in]			size				当たり判定のサイズ
		@param[in]			attack				攻撃力
		@param[in]			attribute			属性
		@param[in]			duration			持続時間
		@return			なし
	*//***********************************************************************/
	MRShotInterface::MRShotInterface(const float x, const float y, const float vx, const float vy,
		const float size, const float attack,
		const constants::MRAttribute attribute, int duration):MRMoverInterface(x, y, size, MRAliveState::ALIVE),
		m_attack(attack), m_attribute(attribute), m_frame(0), m_duration(duration)
	{
		m_transform.SetVelocity(vx, vy);
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param				enemy				敵
		@return			なし
	*//***********************************************************************/
	void MRShotInterface::HitWithEnemy(MREnemyInterface& enemy)
	{
	}
}