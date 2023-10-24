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
		@param[in]		pCamera				�J����
		@param[in]		pMapdata			�}�b�v�f�[�^
		@param[in]		seed				�V�[�h�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRSlime::MRSlime(const float x, const float y, const constants::MRAttribute attribute,
		MRCamera* pCamera, MRMapData* pMapdata, const uint32_t seed)
		:MREnemyInterface(x, y, 1.2f, attribute, pCamera, pMapdata, seed, 1.0f, 6.0f, 12),
		m_animator(0.16f, 4.0f), m_isLeft(false), m_stateMachine(this)
	{
		m_img = &mugen_engine::MECore::GetIns().GetGraph("enemy_slime");

		m_stateMachine.Register(static_cast<int>(STATE::STROLL), &MRSlime::_UpdateOnStroll, &MRSlime::_RenderOnStroll);
		m_stateMachine.Register(static_cast<int>(STATE::CHASE), &MRSlime::_UpdateOnChase, &MRSlime::_RenderOnChase);
		m_stateMachine.ChangeState(static_cast<int>(STATE::STROLL));
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			������
	*//***********************************************************************/
	MREnemyInterface::MRAliveState MRSlime::Update()
	{
		m_stateMachine.Update();
		return m_aliveState;
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::Render() const
	{
		m_stateMachine.Render();
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

	/**********************************************************************//**
		@brief			�p�j���̍X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::_UpdateOnStroll()
	{
		if (m_pMapdata->GetDistancePlayer(m_transform) < 32.0f * 8.0f)
		{
			m_stateMachine.ChangeState(static_cast<int>(STATE::CHASE));
			return;
		}
			m_animator.Update();
		if (!Walk() || m_countWalkFrame > 60 || m_stateMachine.GetFrame() == 0)
		{
			int ret = m_pMapdata->GetRouteToNextRoom(m_transform, m_route);
			m_countWalkFrame = 0;
			if (!ret)
			{
				m_aliveState = MRAliveState::DISAPPEAR;
			}
		}
		m_isLeft = (m_transform.GetVelocityX() < 0.0f);
	}

	/**********************************************************************//**
		@brief			�p�j���̕`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::_RenderOnStroll() const
	{
		m_img->DrawRotaGraph2X(m_pCamera->GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_pCamera->GetAnchoredY(static_cast<int>(m_transform.GetY())),
			1.0f, 0.0f, constants::render_priority::ENEMY, static_cast<int>(m_animator.Get()) + m_isLeft * 5 + m_attribute * 10);
	}

	/**********************************************************************//**
		@brief			�ǐՒ��̍X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::_UpdateOnChase()
	{
		m_animator.Update();
		if (!Walk() || m_countWalkFrame > 60 || m_stateMachine.GetFrame() == 0 || m_stateMachine.GetFrame() > 60)
		{
			int ret = m_pMapdata->GetRouteToPlayer(m_transform, m_route);
			m_countWalkFrame = 0;
			if (!ret)
			{
				m_aliveState = MRAliveState::DISAPPEAR;
			}
		}
		m_isLeft = (m_transform.GetVelocityX() < 0.0f);
	}

	/**********************************************************************//**
		@brief			�ǐՒ��̕`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSlime::_RenderOnChase() const
	{
		m_img->DrawRotaGraph2X(m_pCamera->GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_pCamera->GetAnchoredY(static_cast<int>(m_transform.GetY())),
			1.0f, 0.0f, constants::render_priority::ENEMY, static_cast<int>(m_animator.Get()) + m_isLeft * 5 + m_attribute * 10);
	}
}