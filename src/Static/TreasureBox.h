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
		@brief		�󔠃N���X
	*//***********************************************************************/
	class MRTresureBox : public MRStaticObjectInterface
	{
	public:
		enum class MRRarity : char {
			NORMAL = 0, SILVER, GOLD, RAINBOW
		};
		//! �R���X�g���N�^
		MRTresureBox(const float x, const float y, const MRRarity rarity);
		//! �ʒu�����擾
		MRTransform& GetTransform();
		//! �`��
		void Render(const MRCamera& camera) const;
		
	private:
		MRTransform m_transform;					//!< �ʒu���
		MRRarity m_rarity;							//!< ���A���e�B
		mugen_engine::MEImage* m_image;				//!< �摜
	};
}

#endif//__MagicaRogue_TreasureBox__