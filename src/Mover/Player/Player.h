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
		MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera);
		//! �X�V
		void Update();
		//! �ړ�
		void Move();
		//! �`��
		void Render() const;
		//! �ʒu�����擾
		MRTransform& GetTransform() {
			return m_transform;
		}
		//! �����蔻��̃T�C�Y���擾
		float GetSize() {
			return m_size;
		}
	private:
		PLAYER_ID m_id;										//!< �v���C���[ID
		MRTransform m_transform;							//!< �ʒu���x���
		mugen_engine::MEImage* m_playerImg;					//!< �v���C���[�̃O���t�B�b�N
		mugen_engine::MEImage* m_hpGuageImg;				//!< HP�Q�[�W�̉摜
		MRCamera& m_camera;									//!< �J����
		float m_size;										//!< �v���C���[�̓����蔻��T�C�Y
		float m_speed;										//!< ���@�̈ړ����x
	};
}

#endif//__MagicaRogue_Player__