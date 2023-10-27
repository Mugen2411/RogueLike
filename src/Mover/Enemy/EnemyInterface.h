//! @file EnemyInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyInterface__
#define __MagicaRogue_EnemyInterface__

#include "../MoverInterface.h"
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
	class MREnemyInterface : public MRMoverInterface
	{
	public:
		//! �R���X�g���N�^
		MREnemyInterface(const float x, const float y, const float walkSpeed,
			const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata, const uint32_t seed,
			const float tacklePower, const float tackleKnockback, const int tackleDuration)
			: MRMoverInterface(x, y, 14.0f, MRAliveState::ALIVE), 
			m_pCamera(pCamera), m_pMapdata(pMapdata), m_walkSpeed(walkSpeed),
			m_attribute(attribute), m_random(seed), m_countWalkFrame(0),
			m_tacklePower(tacklePower), m_tackleKnockback(tackleKnockback), m_tackleDuration(tackleDuration){}
		//! �f�X�g���N�^
		virtual ~MREnemyInterface(){}
		//! ���s����
		bool Walk();
		//! �G�ƓG�̉�������
		void HitWithEnemy(MREnemyInterface* rhs);
		//! �v���C���[�Ƃ̓����蔻��
		void HitWithPlayer(MRPlayer& player);

	protected:
		MRCamera *m_pCamera;								//!< �J����
		MRMapData* m_pMapdata;								//!< �}�b�v�f�[�^(���[�g�����p)
		float m_walkSpeed;									//!< �������x
		constants::MRAttribute m_attribute;					//!< ����
		std::vector<MRTransform> m_route;					//!< �������[�g
		MRRandom m_random;									//!< ����������
		int m_countWalkFrame;								//!< �ŋ߂̒��p�n�_�ɒ����܂ł̎���
		float m_tackleKnockback;							//!< �v���C���[�ƂԂ��������ɐ�����΂��З�
		int m_tackleDuration;								//!< �v���C���[�ƂԂ��������Ƀv���C���[�ɗ^����d��
		float m_tacklePower;								//!< �v���C���[�ƂԂ��������Ƀv���C���[�ɗ^����_���[�W
	};
}

#endif//__MagicaRogue_EnemyInterface__