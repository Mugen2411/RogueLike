//! @file EnemyInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyInterface__
#define __MagicaRogue_EnemyInterface__

#include "../../Util/Camera.h"
#include "../../Util/Constants.h"
#include "../../Util/Transform.h"
#include <vector>

namespace magica_rogue
{
	class MRMapData;
	/**********************************************************************//**
		@class		MREnemyInterface
		@brief		敵キャラが必ず継承するインターフェース
	*//***********************************************************************/
	class MREnemyInterface
	{
	public:
		enum class MRAliveState : char {
			ALIVE, DEAD, DISAPPEAR
		};
		//! コンストラクタ
		MREnemyInterface(const float x, const float y, const float walkSpeed,
			const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata)
			:m_pCamera(pCamera), m_pMapdata(pMapdata), m_size(14), m_transform(x, y, 0.0f, 0.0f),
			m_walkSpeed(walkSpeed), m_attribute(attribute), m_state(MRAliveState::ALIVE) {}
		//! 更新
		virtual MRAliveState Update() = 0;
		//! 描画
		virtual void Render() const = 0;
		//! 死んだとき
		virtual void Dead() = 0;
		//! 消えたとき
		virtual void Disappear() = 0;
		//! 歩行する
		bool Walk();
	protected:
		MRCamera *m_pCamera;								//!< カメラ
		MRMapData* m_pMapdata;								//!< マップデータ(ルート検索用)
		size_t m_size;										//!< 当たり判定のサイズ
		MRTransform m_transform;							//!< 位置速度情報
		float m_walkSpeed;									//!< 歩く速度
		constants::MRAttribute m_attribute;					//!< 属性
		MRAliveState m_state;								//!< 生存状況
		std::vector<MRTransform> m_route;					//!< 歩くルート
	};
}

#endif//__MagicaRogue_EnemyInterface__