//! @file EnemyManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyManager.h"
#include "../../Map/MapData.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MREnemyManager::MREnemyManager(): m_maxEnemyNum(0)
	{
	}

	/**********************************************************************//**
		@brief			スポナーの登録
		@param			spawner				スポナー
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::RegisterSpawner(MREnemySpawner spawner)
	{
		m_spawnerList.push_back(spawner);
	}

	/**********************************************************************//**
		@brief			敵を登録
		@param			enemy				敵
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Register(std::unique_ptr<MREnemyInterface>&& enemy)
	{
		if (m_enemyList.size() >= m_maxEnemyNum) return;
		m_enemyList.push_back(std::move(enemy));
	}

	/**********************************************************************//**
		@brief			リセット
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Reset(int maxEnemyNum)
	{
		m_maxEnemyNum = maxEnemyNum;
		m_spawnerList.clear();
		m_enemyList.clear();
	}

	/**********************************************************************//**
		@brief			更新
		@param			mapdata				マップデータ
		@param			player				プレイヤー
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Update(MRMapData& mapdata, MRPlayer& player)
	{
		for (auto& s : m_spawnerList)
		{
			s.Update(*this);
		}
		for (auto itr = m_enemyList.begin(); itr != m_enemyList.end();)
		{
			auto result = (*itr)->Update();

			if (result == MREnemyInterface::MRAliveState::ALIVE)
			{
				++itr;
			}
			else
			{
				if (result == MREnemyInterface::MRAliveState::DEAD)
				{
					(*itr)->Dead();
				}
				if (result == MREnemyInterface::MRAliveState::DISAPPEAR)
				{
					(*itr)->Disappear();
				}
				itr = m_enemyList.erase(itr);
			}
		}
		for (auto& i : m_enemyList)
		{
			for (auto& j : m_enemyList)
			{
				if (i == j) continue;
				i->HitWithEnemy(j.get());
			}
		}
		for (auto& i : m_enemyList)
		{
			i->HitWithPlayer(player);
			mapdata.HitWallWithEnemy(i->GetTransform(), i->GetSize());
			i->Move();
		}
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Render() const
	{
		for (auto& i : m_enemyList)
		{
			i->Render();
		}
	}
}