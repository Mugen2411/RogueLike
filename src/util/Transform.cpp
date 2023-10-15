//! @file Transform.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Transform.h"
#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		x						X���W
		@param[in]		y						Y���W
		@param[in]		vx						X���x
		@param[in]		vy						Y���x
		@return			�Ȃ�
	*//***********************************************************************/
	MRTransform::MRTransform(const float x, const float y, const float vx, const float vy):m_x(x), m_y(y), m_vx(vx), m_vy(vy)
	{}

	/**********************************************************************//**
		@brief			�ʒu��ݒ�
		@param[in]		x						X���W
		@param[in]		y						Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MRTransform::SetPosition(const float x, const float y)
	{
		m_x = x;
		m_y = y;
	}

	/**********************************************************************//**
		@brief			���x��ݒ�
		@param[in]		vx						X���x
		@param[in]		vy						Y���x
		@return			�Ȃ�
	*//***********************************************************************/
	void MRTransform::SetVelocity(const float vx, const float vy)
	{
		m_vx = vx;
		m_vy = vy;
	}

	/**********************************************************************//**
		@brief			�p�x��p���đ��x��ݒ�
		@param[in]		angle					�p�x(���W�A��)
		@param[in]		speed					���x
		@return			�Ȃ�
	*//***********************************************************************/
	void MRTransform::SetVelocityWithAngle(const float angle, const float speed)
	{
		m_vx = std::cosf(angle) * speed;
		m_vy = std::sinf(angle) * speed;
	}

	/**********************************************************************//**
		@brief			�ʒu�����X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRTransform::Update()
	{
		m_x += m_vx;
		m_y += m_vy;
	}
}