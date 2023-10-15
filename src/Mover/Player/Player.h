//! @file Player.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Player__
#define __MagicaRogue_Player__

#include "../../util/Transform.h"
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
		MRPlayer(const PLAYER_ID id, const float x, const float y);
		//! 更新
		void Update();
		//! 描画
		void Render() const;
	private:
		PLAYER_ID m_id;										//!< プレイヤーID
		MRTransform m_transform;							//!< 位置速度情報
		mugen_engine::MEImage* m_playerImg;					//!< プレイヤーのグラフィック
	};
}

#endif//__MagicaRogue_Player__