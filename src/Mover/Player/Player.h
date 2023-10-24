//! @file Player.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Player__
#define __MagicaRogue_Player__

#include "../../Util/Transform.h"
#include "../../Util/Camera.h"
#include "../../Engine/Graphic/GraphicLoadedImage.h"
#include "../../Engine/Graphic/GraphicFontData.h"
#include "../HitPoint.h"
#include "../../Util/StateMachine.h"
#include "../../Util/Animator.h"

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
		enum class STATE
		{
			STAND, KNOCKBACKED
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
		//! ダメージを食らう
		void Damage(const float power, const float knockback, const float angle, const int duration);

		//! 立ち状態での更新
		void UpdateOnStand();
		//! 立ち状態での描画
		void RenderOnStand()const;
		//! のけぞり状態での更新
		void UpdateOnKnockbacked();
		//! のけぞり状態での描画
		void RenderOnKnockbacked()const;
	private:
		PLAYER_ID m_id;										//!< プレイヤーID
		MRTransform m_transform;							//!< 位置速度情報
		mugen_engine::MEImage* m_playerImg;					//!< プレイヤーのグラフィック
		mugen_engine::MEImage* m_hpGuageImg;				//!< HPゲージの画像
		mugen_engine::MEFontData* m_guageFont;				//!< ゲージの実数値を表示するフォント
		MRCamera& m_camera;									//!< カメラ
		float m_size;										//!< プレイヤーの当たり判定サイズ
		float m_speed;										//!< 自機の移動速度
		bool m_isLeft;										//!< 自機が左を向いているか
		int m_frameCount;									//!< 経過したフレーム
		MRAnimator m_animator;								//!< アニメーター
		int m_knockbackDuration;							//!< のけぞる時間
		MRStateMachine<MRPlayer> m_stateMachine;			//!< ステートマシン

		MRHitPoint m_hp;									//!< HP
	};
}

#endif//__MagicaRogue_Player__