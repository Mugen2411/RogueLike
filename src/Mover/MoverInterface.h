//! @file MoverInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MoverInterface__
#define __MagicaRogue_MoverInterface__

#include "../Util/Transform.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMoverInterface
		@brief		���̂��K���p������C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRMoverInterface
	{
	public:
		enum class MRAliveState : char {
			ALIVE, DEAD, DISAPPEAR
		};
		//! �R���X�g���N�^
		MRMoverInterface(const float x, const float y, const float size, const MRAliveState state) :
			m_transform(x, y, 0.0f, 0.0f), m_aliveState(state), m_size(size) {}
		//! �f�X�g���N�^
		virtual ~MRMoverInterface() {}
		//! �ʒu���x���̎擾
		MRTransform& GetTransform() {
			return m_transform;
		}
		//! �T�C�Y�̎擾
		float GetSize() const {
			return m_size;
		}
		virtual MRAliveState Update() = 0;

		/**********************************************************************//**
			@brief			�ړ�
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		virtual void Move() {
			m_transform.Clip();
			m_transform.Update();
		}
		//! �`��
		virtual void Render() const = 0;
		//! ���񂾂Ƃ�
		virtual void Dead() = 0;
		//! �������Ƃ�
		virtual void Disappear() = 0;
	protected:
		MRAliveState m_aliveState;							//!< ������
		float m_size;										//!< �����蔻��̃T�C�Y
		MRTransform m_transform;							//!< �ʒu���x���
	};
}

#endif//__MagicaRogue_MoverInterface__