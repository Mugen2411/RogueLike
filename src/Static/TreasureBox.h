//! @file TreasureBox.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_TreasureBox__
#define __MagicaRogue_TreasureBox__

#include "../Util/Transform.h"
#include "../Util/Camera.h"
#include "../Engine/Graphic/GraphicLoadedImage.h"
#include "StaticObjectInterface.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRTreasureBox
		@brief		宝箱クラス
	*//***********************************************************************/
	class MRTresureBox : public MRStaticObjectInterface
	{
	public:
		enum class MRRarity : char {
			NORMAL = 0, SILVER, GOLD, RAINBOW
		};
		//! コンストラクタ
		MRTresureBox(const float x, const float y, const MRRarity rarity);
		//! 位置情報を取得
		MRTransform& GetTransform();
		//! 描画
		void Render(const MRCamera& camera) const;
		
	private:
		MRTransform m_transform;					//!< 位置情報
		MRRarity m_rarity;							//!< レアリティ
		mugen_engine::MEImage* m_image;				//!< 画像
	};
}

#endif//__MagicaRogue_TreasureBox__