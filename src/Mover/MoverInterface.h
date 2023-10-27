//! @file MoverInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MoverInterface__
#define __MagicaRogue_MoverInterface__

#include "../Util/Transform.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMoverInterface
		@brief		動体が必ず継承するインターフェース
	*//***********************************************************************/
	class MRMoverInterface
	{
	public:
		enum class MRAliveState : char {
			ALIVE, DEAD, DISAPPEAR
		};
		//! コンストラクタ
		MRMoverInterface(const float x, const float y, const float size, const MRAliveState state) :
			m_transform(x, y, 0.0f, 0.0f), m_aliveState(state), m_size(size) {}
		//! デストラクタ
		virtual ~MRMoverInterface() {}
		//! 位置速度情報の取得
		MRTransform& GetTransform() {
			return m_transform;
		}
		//! サイズの取得
		float GetSize() const {
			return m_size;
		}
		virtual MRAliveState Update() = 0;

		/**********************************************************************//**
			@brief			移動
			@param			なし
			@return			なし
		*//***********************************************************************/
		virtual void Move() {
			m_transform.Clip();
			m_transform.Update();
		}
		//! 描画
		virtual void Render() const = 0;
		//! 死んだとき
		virtual void Dead() = 0;
		//! 消えたとき
		virtual void Disappear() = 0;
	protected:
		MRAliveState m_aliveState;							//!< 生存状況
		float m_size;										//!< 当たり判定のサイズ
		MRTransform m_transform;							//!< 位置速度情報
	};
}

#endif//__MagicaRogue_MoverInterface__