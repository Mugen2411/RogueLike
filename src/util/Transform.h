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
		//! ���̃t���[����X���W���擾
		float GetNextX()const {
			return m_x + m_vx;
		}
		//! ���̃t���[����Y���W���擾
		float GetNextY()const {
			return m_y + m_vy;
		}
		//! X���x���擾
		float GetVelocityX()const {
			return m_vx;
		}
		//! Y���x���擾
		float GetVelocityY()const {
			return m_vy;
		}
		//! X���W��ݒ�
		void SetX(float x) {
			m_x = x;
		}
		//! Y���W��ݒ�
		void SetY(float y) {
			m_y = y;
		}
		//! X���x��ݒ�
		void SetVelocityX(float vx) {
			m_vx = vx;
		}
		//! Y���x��ݒ�
		void SetVelocityY(float vy) {
			m_vy = vy;
		}
		float GetDistance2(const MRTransform& rhs)const {
			return (m_x - rhs.m_x) * (m_x - rhs.m_x) + (m_y - rhs.m_y) * (m_y - rhs.m_y);
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