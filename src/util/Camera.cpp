//! @file Camera.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Camera.h"
#include "Constants.h"

#include <cmath>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		x					カメラ左上のX座標
		@param[in]		y					カメラ左上のY座標
		@return			なし
	*//***********************************************************************/
	MRCamera::MRCamera(const int x, const int y): m_anchorX(x), m_anchorY(y)
	{}

	/**********************************************************************//**
		@brief			カメラ左上の座標を設定
		@param[in]		x					カメラ左上のX座標
		@param[in]		y					カメラ左上のY座標
		@return			なし
	*//***********************************************************************/
	void MRCamera::SetAnchor(const int x, const int y)
	{
		m_anchorX = x;
		m_anchorY = y;
	}

	/**********************************************************************//**
		@brief			スクリーン座標のX要素を取得
		@param[in]		x					X座標
		@return			なし
	*//***********************************************************************/
	int MRCamera::GetAnchoredX(const int x) const
	{
		return x - m_anchorX;
	}

	/**********************************************************************//**
		@brief			スクリーン座標のY要素を取得
		@param[in]		y					Y座標
		@return			なし
	*//***********************************************************************/
	int MRCamera::GetAnchoredY(const int y) const
	{
		return y - m_anchorY;
	}
}