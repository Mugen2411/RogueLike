//! @file EnemySpawner.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "EnemyFactory.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			XV
		@param			enemyManager				“G‚ÌŠÇ—Ò
		@return			‚È‚µ
	*//***********************************************************************/
	void MREnemySpawner::Update(MREnemyManager& enemyManager)
	{
		if (m_cnt != 0)
		{
			++m_cnt;
			m_cnt %= m_cycle;
			return;
		}

		for (auto& e : m_enemyDataList)
		{
			for (int i = 0; i < e.count; ++i)
			{
				enemyManager.Register(std::unique_ptr<MREnemyInterface>(MREnemyFactory::GetIns().Create(e.name, m_x, m_y, e.attribute)));
			}
		}
		++m_cnt;
	}
}