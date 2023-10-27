//! @file ShotInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_ShotInterface__
#define __MagicaRogue_ShotInterface__

#include "../MoverInterface.h"
#include "../../Util/Constants.h"

namespace magica_rogue
{
	class MREnemyInterface;
	/**********************************************************************//**
		@class		MRShotInterface
		@brief		���@�V���b�g���K���p������C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRShotInterface : MRMoverInterface
	{
	public:
		//! �R���X�g���N�^
		MRShotInterface(const float x, const float y, const float vx, const float vy, const float size,
			const float attack, const constants::MRAttribute attribute, int duration);
		//! �X�V
		virtual MRAliveState Update() = 0;
		//! �`��
		void Render() const = 0;
		//! �G�Ƃ̓����蔻��
		void HitWithEnemy(MREnemyInterface& enemy);
	private:
		const float m_attack;								//!< �U����
		const constants::MRAttribute m_attribute;			//!< ����
		int m_frame;										//!< ��������Ă���̃t���[����
		const int m_duration;									//!< ������܂ł̎���
	};
}

#endif//__MagicaRogue_ShotInterface__