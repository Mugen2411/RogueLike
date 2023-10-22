//! @file TreasureBox.cpp
//! @note Copyright (c) Mugen_GameLab

#include "TreasureBox.h"
#include "../Engine/Core.h"
#include "../Util/Constants.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		x					X座標
		@param[in]		y					Y座標
		@param[in]		rarity				レアリティ
		@return			なし
	*//***********************************************************************/
	MRTresureBox::MRTresureBox(const float x, const float y, const MRRarity rarity, uint32_t seed)
		: m_transform(x, y, 0.0f, 0.0f), m_rarity(rarity), m_random(seed)
	{
		m_image = &mugen_engine::MECore::GetIns().GetGraph("treasureBox");
	}

	/**********************************************************************//**
		@brief			位置情報を取得する
		@param			なし
		@return			位置情報
	*//***********************************************************************/
	MRTransform& MRTresureBox::GetTransform()
	{
		return m_transform;
	}

	/**********************************************************************//**
		@brief			描画
		@param[in]		camera					カメラ
		@return			なし
	*//***********************************************************************/
	void MRTresureBox::Render(const MRCamera& camera) const
	{
		m_image->DrawGraph2X(camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			camera.GetAnchoredY(static_cast<int>(m_transform.GetY())),
			constants::render_priority::TREASURE_BOX, static_cast<int>(m_rarity));
	}
}