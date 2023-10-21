//! @file Animator.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Animator__
#define __MagicaRogue_Animator__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRAnimator
		@brief		�A�j���[�V�������Ǘ�����N���X
	*//***********************************************************************/
	class MRAnimator
	{
	public:
		//! �R���X�g���N�^
		MRAnimator(float step, float maximum);
		//! �X�V
		void Update();
		//! ���Z�b�g
		void Reset();
		//! ���ݒl���擾
		float Get() const;
	private:
		float m_current;					//!< ���ݒl
		float m_maximum;					//!< �ő�l
		float m_step;						//!< ���t���[�����Z����l
	};
}

#endif//__MagicaRogue_Animator__