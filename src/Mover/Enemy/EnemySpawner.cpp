//! @file EnemySpawner.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "EnemyFactory.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			更新
		@param			enemyManager				敵の管理者
		@return			なし
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
				float x = m_random.GetRanged(m_topX, m_bottomX) * 32.0f + 16.0f;
				float y = m_random.GetRanged(m_topY, m_bottomY) * 32.0f + 16.0f;
				enemyManager.Register(std::unique_ptr<MREnemyInterface>(MREnemyFactory::GetIns().Create(e.name, x, y, e.attribute)));
			}
		}
		++m_cnt;
	}

	/**********************************************************************//**
		@brief			スポナーの追加
		@param			name				召喚する敵の名前
		@param			attribute			召喚する敵の属性
		@param			count				召喚する敵の数
		@return			なし
	*//***********************************************************************/
	void MREnemySpawner::Push(std::string name, constants::MRAttribute attribute, int count)
	{
		m_enemyDataList.push_back(EnemyData{ name, attribute, count });
	}
}