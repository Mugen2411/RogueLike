//! @file Player.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Player__
#define __MagicaRogue_Player__

#include "../../util/Transform.h"
#include "../../util/Camera.h"
#include "../../Engine/Graphic/GraphicLoadedImage.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRPlayer
		@brief		操作出来る自機クラス
	*//***********************************************************************/
	class MRPlayer
	{
	public:
		enum class PLAYER_ID : char {
			AKARI = 0, MAMI, YUKINA, REEZE, 
			IOS, ISHIKI, HARUNA, MISATO,
			SSEL, KOMUK, AKIYO, OBORO
		};
		//! コンストラクタ
		MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera);
		//! 更新
		void Update();
		//! 移動
		void Move();
		//! 描画
		void Render() const;
		//! 位置情報を取得
		MRTransform& GetTransform() {
			return m_transform;
		}
		//! 当たり判定のサイズを取得
		float GetSize() {
			return m_size;
		}
	private:
		PLAYER_ID m_id;										//!< プレイヤーID
		MRTransform m_transform;							//!< 位置速度情報
		mugen_engine::MEImage* m_playerImg;					//!< プレイヤーのグラフィック
		mugen_engine::MEImage* m_hpGuageImg;				//!< HPゲージの画像
		MRCamera& m_camera;									//!< カメラ
		float m_size;										//!< プレイヤーの当たり判定サイズ
		float m_speed;										//!< 自機の移動速度
	};
}

#endif//__MagicaRogue_Player__