//! @file Camera.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Camera.h"
#include "Constants.h"

#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		x					�J���������X���W
		@param[in]		y					�J���������Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	MRCamera::MRCamera(const int x, const int y): m_anchorX(x), m_anchorY(y)
	{}

	/**********************************************************************//**
		@brief			�J��������̍��W��ݒ�
		@param[in]		x					�J���������X���W
		@param[in]		y					�J���������Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MRCamera::SetAnchor(const int x, const int y)
	{
		m_anchorX = x;
		m_anchorY = y;
	}

	/**********************************************************************//**
		@brief			�X�N���[�����W��X�v�f���擾
		@param[in]		x					X���W
		@return			�Ȃ�
	*//***********************************************************************/
	int MRCamera::GetAnchoredX(const int x) const
	{
		return x - m_anchorX;
	}

	/**********************************************************************//**
		@brief			�X�N���[�����W��Y�v�f���擾
		@param[in]		y					Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	int MRCamera::GetAnchoredY(const int y) const
	{
		return y - m_anchorY;
	}
}