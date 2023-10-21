//! @file EnemyInterface.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyInterface.h"
#include "../../Map/MapData.h"
#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			歩行する
		@param			なし
		@return			次に進むルートがあればtrue, 無ければfalse
	*//***********************************************************************/
	bool MREnemyInterface::Walk()
	{
		if (m_route.empty())
		{
			return false;
		}
		if (m_transform.GetDistance2(m_route.back()) < 8.0f)
		{
			m_route.pop_back();
		}
		if (m_route.empty())
		{
			return false;
		}
		m_transform.SetVelocityWithAngle(std::atan2f(m_route.back().GetY() - m_transform.GetY(),
			m_route.back().GetX() - m_transform.GetX()), m_walkSpeed);
		return true;
	}
}