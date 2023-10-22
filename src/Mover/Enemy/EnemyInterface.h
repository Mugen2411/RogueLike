//! @file EnemyInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyInterface__
#define __MagicaRogue_EnemyInterface__

#include "../../Util/Camera.h"
#include "../../Util/Constants.h"
#include "../../Util/Transform.h"
#include "../../Util/Random.h"
#include <vector>

namespace magica_rogue
{
	class MRPlayer;
	class MRMapData;
	/**********************************************************************//**
		@class		MREnemyInterface
		@brief		�G�L�������K���p������C���^�[�t�F�[�X
	*//***********************************************************************/
	class MREnemyInterface
	{
	public:
		enum class MRAliveState : char {
			ALIVE, DEAD, DISAPPEAR
		};
		//! �R���X�g���N�^
		MREnemyInterface(const float x, const float y, const float walkSpeed,
			const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata, const uint32_t seed,
			const float tacklePower, const float tackleKnockback, const int tackleDuration)
			:m_pCamera(pCamera), m_pMapdata(pMapdata), m_size(14.0f), m_transform(x, y, 0.0f, 0.0f),
			m_walkSpeed(walkSpeed), m_attribute(attribute), m_state(MRAliveState::ALIVE), m_random(seed), m_countWalkFrame(0),
			m_tacklePower(tacklePower), m_tackleKnockback(tackleKnockback), m_tackleDuration(tackleDuration){}
		//! �f�X�g���N�^
		virtual ~MREnemyInterface(){}
		//! �X�V
		virtual MRAliveState Update() = 0;
		//! �ړ�
		void Move();
		//! �`��
		virtual void Render() const = 0;
		//! ���񂾂Ƃ�
		virtual void Dead() = 0;
		//! �������Ƃ�
		virtual void Disappear() = 0;
		//! ���s����
		bool Walk();
		//! �G�ƓG�̉�������
		void HitWithEnemy(MREnemyInterface* rhs);
		//! �ʒu���x���̎擾
		MRTransform& GetTransform() {
			return m_transform;
		}
		//! �v���C���[�Ƃ̓����蔻��
		void HitWithPlayer(MRPlayer& player);
		//! �T�C�Y�̎擾
		float GetSize() const {
			return m_size;
		}
	protected:
		MRCamera *m_pCamera;								//!< �J����
		MRMapData* m_pMapdata;								//!< �}�b�v�f�[�^(���[�g�����p)
		float m_size;										//!< �����蔻��̃T�C�Y
		MRTransform m_transform;							//!< �ʒu���x���
		float m_walkSpeed;									//!< �������x
		constants::MRAttribute m_attribute;					//!< ����
		MRAliveState m_state;								//!< ������
		std::vector<MRTransform> m_route;					//!< �������[�g
		MRRandom m_random;									//!< ����������
		int m_countWalkFrame;								//!< �ŋ߂̒��p�n�_�ɒ����܂ł̎���
		float m_tackleKnockback;							//!< �v���C���[�ƂԂ��������ɐ�����΂��З�
		int m_tackleDuration;								//!< �v���C���[�ƂԂ��������Ƀv���C���[�ɗ^����d��
		float m_tacklePower;								//!< �v���C���[�ƂԂ��������Ƀv���C���[�ɗ^����_���[�W
	};
}

#endif//__MagicaRogue_EnemyInterface__