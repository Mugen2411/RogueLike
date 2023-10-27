//! @file Player.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Player__
#define __MagicaRogue_Player__

#include "../MoverInterface.h"
#include "../../Util/Transform.h"
#include "../../Util/Camera.h"
#include "../../Engine/Graphic/GraphicLoadedImage.h"
#include "../../Engine/Graphic/GraphicFontData.h"
#include "../HitPoint.h"
#include "../MagicPoint.h"
#include "../../Util/StateMachine.h"
#include "../../Util/Animator.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRPlayer
		@brief		����o���鎩�@�N���X
	*//***********************************************************************/
	class MRPlayer : public MRMoverInterface
	{
	public:
		enum class PLAYER_ID : char {
			AKARI = 0, MAMI, YUKINA, REEZE, 
			IOS, ISHIKI, HARUNA, MISATO,
			SSEL, KOMUK, AKIYO, OBORO
		};
		enum class STATE
		{
			STAND, KNOCKBACKED
		};
		//! �R���X�g���N�^
		MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera);
		//! �X�V
		MRAliveState Update();
		//! �ړ�
		void Move();
		//! �`��
		void Render() const;
		//! ���񂾂Ƃ�
		void Dead() {}
		//! �������Ƃ�
		void Disappear() {}
		//! �_���[�W��H�炤
		void Damage(const float power, const float knockback, const float angle, const int duration);

		//! ������Ԃł̍X�V
		void UpdateOnStand();
		//! ������Ԃł̕`��
		void RenderOnStand()const;
		//! �̂������Ԃł̍X�V
		void UpdateOnKnockbacked();
		//! �̂������Ԃł̕`��
		void RenderOnKnockbacked()const;
	private:
		//! �V���b�g������
		void _Shot();

		PLAYER_ID m_id;										//!< �v���C���[ID
		mugen_engine::MEImage* m_playerImg;					//!< �v���C���[�̃O���t�B�b�N
		mugen_engine::MEImage* m_hpGuageImg;				//!< HP�Q�[�W�̉摜
		mugen_engine::MEImage* m_aimImg;					//!< �Ə��̉摜
		mugen_engine::MEFontData* m_guageFont;				//!< �Q�[�W�̎����l��\������t�H���g
		MRCamera& m_camera;									//!< �J����
		float m_speed;										//!< ���@�̈ړ����x
		bool m_isLeft;										//!< ���@�����������Ă��邩
		int m_frameCount;									//!< �o�߂����t���[��
		MRAnimator m_animator;								//!< �A�j���[�^�[
		int m_knockbackDuration;							//!< �̂����鎞��
		MRStateMachine<MRPlayer> m_stateMachine;			//!< �X�e�[�g�}�V��

		MRHitPoint m_hp;									//!< HP
		MRMagicPoint m_mp;									//!< MP
	};
}

#endif//__MagicaRogue_Player__