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
		@brief		敵の管理をするクラス
	*//***********************************************************************/
	class MREnemyManager
	{
	public:
		//! コンストラクタ
		MREnemyManager();
		//! スポナーを登録
		void RegisterSpawner(MREnemySpawner spawner);
		//! 敵を登録
		void Register(std::unique_ptr<MREnemyInterface>&& enemy);
		//! リセット
		void Reset();
		//! 更新
		void Update();
		//! 描画
		void Render()const;
	private:
		std::list<std::unique_ptr<MREnemyInterface>> m_enemyList;		//!< 敵リスト
		std::list<MREnemySpawner> m_spawnerList;						//!< スポナーリスト
	};
}

#endif//__MagicaRogue_EnemyManager__