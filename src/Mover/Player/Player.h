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
		@brief		����o���鎩�@�N���X
	*//***********************************************************************/
	class MRPlayer
	{
	public:
		enum class PLAYER_ID : char {
			AKARI = 0, MAMI, YUKINA, REEZE, 
			IOS, ISHIKI, HARUNA, MISATO,
			SSEL, KOMUK, AKIYO, OBORO
		};
		//! �R���X�g���N�^
		MRPlayer(const PLAYER_ID id, const float x, const float y);
		//! �X�V
		void Update();
		//! �`��
		void Render() const;
	private:
		PLAYER_ID m_id;										//!< �v���C���[ID
		MRTransform m_transform;							//!< �ʒu���x���
		mugen_engine::MEImage* m_playerImg;					//!< �v���C���[�̃O���t�B�b�N
	};
}

#endif//__MagicaRogue_Player__