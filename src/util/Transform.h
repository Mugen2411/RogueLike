//! @file Transform.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Transform__
#define __MagicaRogue_Transform__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRTransform
		@brief		���̂̍��W�Ƒ��x�������N���X
	*//***********************************************************************/
	class MRTransform
	{
	public:
		//! �R���X�g���N�^
		MRTransform(const float x, const float y, const float vx, const float vy);
		//! �ʒu��ݒ�
		void SetPosition(const float x, const float y);
		//! ���x��ݒ�
		void SetVelocity(const float vx, const float vy);
		//! ���x���p�x��p���Đݒ�
		void SetVelocityWithAngle(const float angle, const float speed);
		//! X���W���擾
		float GetX()const {
			return m_x;
		}
		//! Y���W���擾
		float GetY()const {
			return m_y;
		}
		//! �ʒu�����X�V
		void Update();

	private:
		float m_x;											//!< X���W
		float m_y;											//!< Y���W
		float m_vx;											//!< X���x
		float m_vy;											//!< Y���x
	};
}

#endif//__MagicaRogue_Transform__