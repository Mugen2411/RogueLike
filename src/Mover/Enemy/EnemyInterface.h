//! @file EnemyInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyInterface__
#define __MagicaRogue_EnemyInterface__

#include "../../Util/Camera.h"
#include "../../Util/Constants.h"
#include "../../Util/Transform.h"
#include <vector>

namespace magica_rogue
{
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
			const constants::MRAttribute attribute, MRCamera *pCamera, MRMapData* pMapdata)
			:m_pCamera(pCamera), m_pMapdata(pMapdata), m_size(14), m_transform(x, y, 0.0f, 0.0f),
			m_walkSpeed(walkSpeed), m_attribute(attribute), m_state(MRAliveState::ALIVE) {}
		//! �X�V
		virtual MRAliveState Update() = 0;
		//! �`��
		virtual void Render() const = 0;
		//! ���񂾂Ƃ�
		virtual void Dead() = 0;
		//! �������Ƃ�
		virtual void Disappear() = 0;
		//! ���s����
		bool Walk();
	protected:
		MRCamera *m_pCamera;								//!< �J����
		MRMapData* m_pMapdata;								//!< �}�b�v�f�[�^(���[�g�����p)
		size_t m_size;										//!< �����蔻��̃T�C�Y
		MRTransform m_transform;							//!< �ʒu���x���
		float m_walkSpeed;									//!< �������x
		constants::MRAttribute m_attribute;					//!< ����
		MRAliveState m_state;								//!< ������
		std::vector<MRTransform> m_route;					//!< �������[�g
	};
}

#endif//__MagicaRogue_EnemyInterface__