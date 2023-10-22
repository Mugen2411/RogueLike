//! @file EnemySpawner.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemySpawner__
#define __MagicaRogue_EnemySpawner__

#include <vector>
#include <string>
#include "../../Util/Constants.h"
#include "../../Util/Random.h"

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
		MREnemySpawner(const int topX, const int topY, const int bottomX, const int bottomY, const int cycle, uint32_t seed)
			:m_cycle(cycle), m_cnt(0), m_topX(topX), m_topY(topY), m_bottomX(bottomX), m_bottomY(bottomY), m_random(seed)
		{
			m_cnt = m_random.GetRanged(0, m_cycle);
		}
		//! 更新
		void Update(MREnemyManager& enemyManager);
		//! 敵データを追加する
		void Push(std::string name, constants::MRAttribute attribute, int count);
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
		int m_topX;									//!< 左上のX座標
		int m_topY;									//!< 左上のY座標
		int m_bottomX;								//!< 右下のX座標
		int m_bottomY;								//!< 右下のY座標
		MRRandom m_random;							//!< 乱数生成器
	};
}

#endif//__MagicaRogue_EnemySpawner__