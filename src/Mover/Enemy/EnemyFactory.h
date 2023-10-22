//! @file EnemyFactory.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyFactory__
#define __MagicaRogue_EnemyFactory__

#include <memory>
#include <string>
#include "EnemyInterface.h"
#include "../../Map/MapData.h"
#include "../../Util/Constants.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MREnemyFactory
		@brief		敵を実際に生成するクラス
	*//***********************************************************************/
	class MREnemyFactory
	{
	public:
		//! インスタンスの取得
		static MREnemyFactory& GetIns();
		//! 初期化
		void Initialize(MRCamera& camera, MRMapData& mapdata);
		//! 生成
		MREnemyInterface* Create(std::string name,
			const float x, const float y, const constants::MRAttribute attribute);
	private:
		//! コンストラクタ
		MREnemyFactory();

		MRCamera* m_pCamera;				//!< カメラ
		MRMapData* m_pMapdata;				//!< マップデータ
		MRRandom m_random;					//!< 乱数生成器
	};
}

#endif//__MagicaRogue_EnemyFactory__