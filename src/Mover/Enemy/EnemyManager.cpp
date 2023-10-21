//! @file EnemyManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MREnemyManager::MREnemyManager()
	{
	}

	/**********************************************************************//**
		@brief			�X�|�i�[�̓o�^
		@param			spawner				�X�|�i�[
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyManager::RegisterSpawner(MREnemySpawner spawner)
	{
		m_spawnerList.push_back(spawner);
	}

	/**********************************************************************//**
		@brief			�G��o�^
		@param			enemy				�G
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyManager::Register(std::unique_ptr<MREnemyInterface>&& enemy)
	{
		m_enemyList.push_back(std::move(enemy));
	}

	/**********************************************************************//**
		@brief			���Z�b�g
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyManager::Reset()
	{
		m_spawnerList.clear();
		m_enemyList.clear();
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			�Ȃ�
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
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyManager::Render() const
	{
		for (auto& i : m_enemyList)
		{
			i->Render();
		}
	}
}