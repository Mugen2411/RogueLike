//! @file EnemyManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MREnemyManager::MREnemyManager()
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
		m_enemyList.push_back(std::move(enemy));
	}

	/**********************************************************************//**
		@brief			リセット
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Reset()
	{
		m_spawnerList.clear();
		m_enemyList.clear();
	}

	/**********************************************************************//**
		@brief			更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MREnemyManager::Update()
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