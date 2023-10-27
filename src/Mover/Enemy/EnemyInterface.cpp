//! @file EnemyInterface.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyInterface.h"
#include "../../Map/MapData.h"
#include "../Player/Player.h"
#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			���s����
		@param			�Ȃ�
		@return			���ɐi�ރ��[�g�������true, �������false
	*//***********************************************************************/
	bool MREnemyInterface::Walk()
	{
		if (m_route.empty())
		{
			m_countWalkFrame = 0;
			return false;
		}
		if (m_transform.GetDistance2(m_route.back()) < 16.0f)
		{
			m_route.pop_back();
			m_countWalkFrame = 0;
		}
		if (m_route.empty())
		{
			m_countWalkFrame = 0;
			return false;
		}
		m_transform.SetVelocityWithAngle(std::atan2f(m_route.back().GetY() - m_transform.GetY(),
			m_route.back().GetX() - m_transform.GetX()), m_walkSpeed);
		++m_countWalkFrame;
		return true;
	}

	/**********************************************************************//**
		@brief			�G�ƓG�̉�������
		@param			rhs					�Ԃ���G
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyInterface::HitWithEnemy(MREnemyInterface* rhs)
	{
		constexpr float hitSizeRatio = 10.0f;
		auto& t = rhs->m_transform;
		float dist2 = m_transform.GetDistance2(t);
		float maxDist2 = (m_size + rhs->m_size) * (m_size + rhs->m_size);
		constexpr float inv = 1.0f / 20.0f;
		if (dist2 < maxDist2)
		{
			m_transform.AddVelocityWithAngle(std::atan2f(m_transform.GetY() - t.GetY(), m_transform.GetX() - t.GetX())
				+ m_random.GetRanged(-24, 24) * constants::math::pi2 / 256.0f,
				static_cast<float>(inv * (m_size + rhs->m_size) * min(maxDist2 / dist2, hitSizeRatio)));
		}
	}

	/**********************************************************************//**
		@brief			�G�ƃv���C���[�̓����蔻��
		@param			player				�v���C���[
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyInterface::HitWithPlayer(MRPlayer& player)
	{
		auto playerTransform = player.GetTransform();
		if (playerTransform.GetDistance2(this->m_transform) > (player.GetSize() + this->m_size)* (player.GetSize() + this->m_size))
		{
			return;
		}
		player.Damage(m_tacklePower, m_tackleKnockback,
			std::atan2f(playerTransform.GetY() - m_transform.GetY(), playerTransform.GetX() - m_transform.GetX()), m_tackleDuration);
	}
}