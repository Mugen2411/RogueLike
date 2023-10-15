//! @file Transform.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Transform.h"
#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		x						X座標
		@param[in]		y						Y座標
		@param[in]		vx						X速度
		@param[in]		vy						Y速度
		@return			なし
	*//***********************************************************************/
	MRTransform::MRTransform(const float x, const float y, const float vx, const float vy):m_x(x), m_y(y), m_vx(vx), m_vy(vy)
	{}

	/**********************************************************************//**
		@brief			位置を設定
		@param[in]		x						X座標
		@param[in]		y						Y座標
		@return			なし
	*//***********************************************************************/
	void MRTransform::SetPosition(const float x, const float y)
	{
		m_x = x;
		m_y = y;
	}

	/**********************************************************************//**
		@brief			速度を設定
		@param[in]		vx						X速度
		@param[in]		vy						Y速度
		@return			なし
	*//***********************************************************************/
	void MRTransform::SetVelocity(const float vx, const float vy)
	{
		m_vx = vx;
		m_vy = vy;
	}

	/**********************************************************************//**
		@brief			角度を用いて速度を設定
		@param[in]		angle					角度(ラジアン)
		@param[in]		speed					速度
		@return			なし
	*//***********************************************************************/
	void MRTransform::SetVelocityWithAngle(const float angle, const float speed)
	{
		m_vx = std::cosf(angle) * speed;
		m_vy = std::sinf(angle) * speed;
	}

	/**********************************************************************//**
		@brief			位置情報を更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRTransform::Update()
	{
		m_x += m_vx;
		m_y += m_vy;
	}
}