//! @file ShotInterface.cpp
//! @note Copyright (c) Mugen_GameLab

#include "ShotInterface.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]			x					X���W
		@param[in]			y					Y���W
		@param[in]			size				�����蔻��̃T�C�Y
		@param[in]			attack				�U����
		@param[in]			attribute			����
		@param[in]			duration			��������
		@return			�Ȃ�
	*//***********************************************************************/
	MRShotInterface::MRShotInterface(const float x, const float y, const float vx, const float vy,
		const float size, const float attack,
		const constants::MRAttribute attribute, int duration):MRMoverInterface(x, y, size, MRAliveState::ALIVE),
		m_attack(attack), m_attribute(attribute), m_frame(0), m_duration(duration)
	{
		m_transform.SetVelocity(vx, vy);
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param				enemy				�G
		@return			�Ȃ�
	*//***********************************************************************/
	void MRShotInterface::HitWithEnemy(MREnemyInterface& enemy)
	{
	}
}