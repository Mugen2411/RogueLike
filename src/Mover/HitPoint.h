//! @file HitPoint.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_HitPoint__
#define __MagicaRogue_HitPoint__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRHitPoint
		@brief		�̗͂������N���X
	*//***********************************************************************/
	class MRHitPoint
	{
	public:
		//! �R���X�g���N�^
		MRHitPoint(const float maximumValue);
		//! ��
		void Heal(const float value);
		//! ������
		void RatioHeal(const float ratio);
		//! �_���[�W
		void Damage(const float value);
		//! ���݂�HP���擾
		float GetValue()const {
			return m_value;
		}
		//! ���݂�HP�̊������擾
		float GetRatio()const {
			return m_value / m_maximum;
		}
		//! �ő�l���擾
		float GetMax()const {
			return m_maximum;
		}
	private:
		float m_value;									//!< ���ݒl
		float m_maximum;								//!< �ő�l
	};
}

#endif//__MagicaRogue_HitPoint__