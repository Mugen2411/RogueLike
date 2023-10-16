//! @file Camera.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Camera__
#define __MagicaRogue_Camera__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRCamera
		@brief		�X�N���[���@�\�ƃJ�����������N���X
	*//***********************************************************************/
	class MRCamera
	{
	public:
		//! �R���X�g���N�^
		MRCamera(const int x, const int y);
		//! �J�����̍�����W��ݒ�
		void SetAnchor(const int x, const int y);
		//! �X�N���[�����W��X�v�f���擾
		int GetAnchoredX(const int x) const;
		//! �X�N���[�����W��Y�v�f���擾
		int GetAnchoredY(const int y) const;
	private:
		int m_anchorX;						//!< �J���������X���W
		int m_anchorY;						//!< �J���������Y���W
	};
}

#endif//__MagicaRogue_Camera__