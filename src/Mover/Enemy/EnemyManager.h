//! @file EnemyManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyManager__
#define __MagicaRogue_EnemyManager__

#include "EnemyInterface.h"
#include "EnemySpawner.h"
#include <list>
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MREnemyManager
		@brief		�G�̊Ǘ�������N���X
	*//***********************************************************************/
	class MREnemyManager
	{
	public:
		//! �R���X�g���N�^
		MREnemyManager();
		//! �X�|�i�[��o�^
		void RegisterSpawner(MREnemySpawner spawner);
		//! �G��o�^
		void Register(std::unique_ptr<MREnemyInterface>&& enemy);
		//! ���Z�b�g
		void Reset();
		//! �X�V
		void Update();
		//! �`��
		void Render()const;
	private:
		std::list<std::unique_ptr<MREnemyInterface>> m_enemyList;		//!< �G���X�g
		std::list<MREnemySpawner> m_spawnerList;						//!< �X�|�i�[���X�g
	};
}

#endif//__MagicaRogue_EnemyManager__