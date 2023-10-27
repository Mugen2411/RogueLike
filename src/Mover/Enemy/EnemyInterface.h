//! @file EnemyInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyInterface__
#define __MagicaRogue_EnemyInterface__

#include "../MoverInterface.h"
#include "../../Util/Camera.h"
#include "../../Util/Constants.h"
#include "../../Util/Transform.h"
#include "../../Util/Random.h"
#include <vector>

namespace magica_rogue
{
	class MRPlayer;
	class MRMapData;
	/**********************************************************************//**
		@class		MREnemyInterface
		@brief		敵キャラが必ず継承するインターフェース
	*//***********************************************************************/
	class MREnemyInterface : public MRMoverInterface
	{
	public:
		//! コンストラクタ
		MREnemyInterface(const float x, const float y, const float walkSpeed,
			const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata, const uint32_t seed,
			const float tacklePower, const float tackleKnockback, const int tackleDuration)
			: MRMoverInterface(x, y, 14.0f, MRAliveState::ALIVE), 
			m_pCamera(pCamera), m_pMapdata(pMapdata), m_walkSpeed(walkSpeed),
			m_attribute(attribute), m_random(seed), m_countWalkFrame(0),
			m_tacklePower(tacklePower), m_tackleKnockback(tackleKnockback), m_tackleDuration(tackleDuration){}
		//! デストラクタ
		virtual ~MREnemyInterface(){}
		//! 歩行する
		bool Walk();
		//! 敵と敵の押し合い
		void HitWithEnemy(MREnemyInterface* rhs);
		//! プレイヤーとの当たり判定
		void HitWithPlayer(MRPlayer& player);

	protected:
		MRCamera *m_pCamera;								//!< カメラ
		MRMapData* m_pMapdata;								//!< マップデータ(ルート検索用)
		float m_walkSpeed;									//!< 歩く速度
		constants::MRAttribute m_attribute;					//!< 属性
		std::vector<MRTransform> m_route;					//!< 歩くルート
		MRRandom m_random;									//!< 乱数生成器
		int m_countWalkFrame;								//!< 最近の中継地点に着くまでの時間
		float m_tackleKnockback;							//!< プレイヤーとぶつかった時に吹き飛ばす威力
		int m_tackleDuration;								//!< プレイヤーとぶつかった時にプレイヤーに与える硬直
		float m_tacklePower;								//!< プレイヤーとぶつかった時にプレイヤーに与えるダメージ
	};
}

#endif//__MagicaRogue_EnemyInterface__