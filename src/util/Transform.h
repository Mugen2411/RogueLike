//! @file Transform.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Transform__
#define __MagicaRogue_Transform__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRTransform
		@brief		物体の座標と速度を扱うクラス
	*//***********************************************************************/
	class MRTransform
	{
	public:
		//! コンストラクタ
		MRTransform(const float x, const float y, const float vx, const float vy);
		//! 位置を設定
		void SetPosition(const float x, const float y);
		//! 速度を設定
		void SetVelocity(const float vx, const float vy);
		//! 速度を角度を用いて設定
		void SetVelocityWithAngle(const float angle, const float speed);
		//! X座標を取得
		float GetX()const {
			return m_x;
		}
		//! Y座標を取得
		float GetY()const {
			return m_y;
		}
		//! 次のフレームのX座標を取得
		float GetNextX()const {
			return m_x + m_vx;
		}
		//! 次のフレームのY座標を取得
		float GetNextY()const {
			return m_y + m_vy;
		}
		//! X速度を取得
		float GetVelocityX()const {
			return m_vx;
		}
		//! Y速度を取得
		float GetVelocityY()const {
			return m_vy;
		}
		//! X座標を設定
		void SetX(float x) {
			m_x = x;
		}
		//! Y座標を設定
		void SetY(float y) {
			m_y = y;
		}
		//! X速度を設定
		void SetVelocityX(float vx) {
			m_vx = vx;
		}
		//! Y速度を設定
		void SetVelocityY(float vy) {
			m_vy = vy;
		}
		float GetDistance2(const MRTransform& rhs)const {
			return (m_x - rhs.m_x) * (m_x - rhs.m_x) + (m_y - rhs.m_y) * (m_y - rhs.m_y);
		}
		//! 位置情報を更新
		void Update();

	private:
		float m_x;											//!< X座標
		float m_y;											//!< Y座標
		float m_vx;											//!< X速度
		float m_vy;											//!< Y速度
	};
}

#endif//__MagicaRogue_Transform__