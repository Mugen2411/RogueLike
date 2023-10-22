//! @file Slime.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Slime.h"
#include "../../../Map/MapData.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		x					X���W
		@param[in]		y					Y���W
		@param[in]		attribute			����
		@param[in]		camera				�J����
		@param[in]		seed				�V�[�h�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRSlime::MRSlime(const float x, const float y, const constants::MRAttribute attribute,
		MRCamera* pCamera, MRMapData* pMapdata, const uint32_t seed)
		:MREnemyInterface(x, y, 1.2f, attribute, pCamera, pMapdata, seed), m_animator(0.16f, 4.0f)
	{
		m_img = &mugen_engine::MECore::GetIns().GetGraph("enemy_slime");
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			������
	*//***********************************************************************/
	MREnemyInterface::MRAliveState MRSlime::Update()
	{
		m_animator.Update();
		if (!Walk() || m_countWalkFrame > 60)
		{
			m_pMapdata->GetRouteToNextRoom(m_transform, m_route);
			m_countWalkFrame = 0;
		}
		m_isLeft = (m_transform.GetVelocityX() < 0.0f);
		return m_state;
	}

	/**********************************************************************//**
		@brief			�ړ�
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::Move()
	{
		m_transform.Update();
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::Render() const
	{
		m_img->DrawRotaGraph2X(m_pCamera->GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_pCamera->GetAnchoredY(static_cast<int>(m_transform.GetY())),
			1.0f, 0.0f, constants::render_priority::ENEMY, static_cast<int>(m_animator.Get()) + m_isLeft * 5 + m_attribute * 10);
	}

	/**********************************************************************//**
		@brief			���񂾂Ƃ��̏���
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::Dead()
	{
	}

	/**********************************************************************//**
		@brief			�������Ƃ��̏���
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::Disappear()
	{
	}
}