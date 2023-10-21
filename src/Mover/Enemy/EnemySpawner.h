//! @file EnemySpawner.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemySpawner__
#define __MagicaRogue_EnemySpawner__

#include <vector>
#include <string>
#include "../../Util/Constants.h"

namespace magica_rogue
{
	class MREnemyManager;
	/**********************************************************************//**
		@class		MREnemySpawner
		@brief		敵のスポナークラス
	*//***********************************************************************/
	class MREnemySpawner
	{
	public:
		//! コンストラクタ
		MREnemySpawner(const float x, const float y, const int cycle)
			:m_cycle(cycle), m_cnt(0), m_x(x), m_y(y)
		{
			m_enemyDataList.push_back(EnemyData{ "slime", constants::MRAttribute::ABYSS, 1 });
		}
		//! 更新
		void Update(MREnemyManager& enemyManager);
	private:
		/**********************************************************************//**
			@struct		EnemyData
			@brief		敵の召喚に必要なデータ
		*//***********************************************************************/
		struct EnemyData
		{
			std::string name;						//!< 召喚する敵の名前
			constants::MRAttribute attribute;		//!< 召喚する属性
			int count;								//!< 召喚する数
		};

		std::vector<EnemyData> m_enemyDataList;		//!< 召喚するべき敵のリスト
		int m_cycle;								//!< 敵を召喚する周期
		int m_cnt;									//!< 経過時間(フレーム)
		float m_x;									//!< X座標
		float m_y;									//!< Y座標
	};
}

#endif//__MagicaRogue_EnemySpawner__