//! @file TreasureBox.cpp
//! @note Copyright (c) Mugen_GameLab

#include "TreasureBox.h"
#include "../Engine/Core.h"
#include "../Util/Constants.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		x					X���W
		@param[in]		y					Y���W
		@param[in]		rarity				���A���e�B
		@return			�Ȃ�
	*//***********************************************************************/
	MRTresureBox::MRTresureBox(const float x, const float y, const MRRarity rarity, uint32_t seed)
		: m_transform(x, y, 0.0f, 0.0f), m_rarity(rarity), m_random(seed)
	{
		m_image = &mugen_engine::MECore::GetIns().GetGraph("treasureBox");
	}

	/**********************************************************************//**
		@brief			�ʒu�����擾����
		@param			�Ȃ�
		@return			�ʒu���
	*//***********************************************************************/
	MRTransform& MRTresureBox::GetTransform()
	{
		return m_transform;
	}

	/**********************************************************************//**
		@brief			�`��
		@param[in]		camera					�J����
		@return			�Ȃ�
	*//***********************************************************************/
	void MRTresureBox::Render(const MRCamera& camera) const
	{
		m_image->DrawGraph2X(camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			camera.GetAnchoredY(static_cast<int>(m_transform.GetY())),
			constants::render_priority::TREASURE_BOX, static_cast<int>(m_rarity));
	}
}