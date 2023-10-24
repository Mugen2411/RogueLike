//! @file Slime.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Enemy_Slime__
#define __MagicaRogue_Enemy_Slime__

#include "../EnemyInterface.h"
#include "../../../Engine/Core.h"
#include "../../../Util/Animator.h"
#include "../../../Util/StateMachine.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSlime
		@brief		�G�u�X���C���v��\������N���X
	*//***********************************************************************/
	class MRSlime : public MREnemyInterface
	{
	public:
		//! �R���X�g���N�^
		MRSlime(const float x, const float y, const constants::MRAttribute attribute,
			MRCamera *pCamera, MRMapData* pMapdata, const uint32_t seed);
		//! �X�V
		MRAliveState Update();
		//! �`��
		void Render() const;
		//! ���񂾂Ƃ�
		void Dead();
		//! �������Ƃ�
		void Disappear();
	private:
		enum class STATE {
			STROLL,				//!< �p�j
			CHASE,				//!< �ǐ�
			KNOCKBACKED			//!< �m�b�N�o�b�N
		};

		//! �p�j���̍X�V
		void _UpdateOnStroll();
		//! �p�j���̕`��
		void _RenderOnStroll() const;
		//! �ǐՒ��̍X�V
		void _UpdateOnChase();
		//! �ǐՒ��̕`��
		void _RenderOnChase() const;

		mugen_engine::MEImage* m_img;						//!< �摜
		MRAnimator m_animator;								//!< �A�j���[�^�[
		bool m_isLeft;										//!< ���������Ă��邩
		MRStateMachine<MRSlime> m_stateMachine;				//!< �X�e�[�g�}�V��
	};
}

#endif//__MagicaRogue_Enemy_Slime__
