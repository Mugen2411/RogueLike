//! @file Player.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Player.h"
#include "../../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		id						�v���C���[ID
		@param[in]		x						X���W
		@param[in]		y						Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	MRPlayer::MRPlayer(const PLAYER_ID id, const float x, const float y): m_id(id), m_transform(x, y, 0.0f, 0.0f)
	{
		switch (id)
		{
		case PLAYER_ID::AKARI:
			break;
		case PLAYER_ID::MAMI:
			break;
		case PLAYER_ID::YUKINA:
			break;
		case PLAYER_ID::REEZE:
			break;
		case PLAYER_ID::IOS:
			break;
		case PLAYER_ID::ISHIKI:
			break;
		case PLAYER_ID::HARUNA:
			break;
		case PLAYER_ID::MISATO:
			break;
		case PLAYER_ID::SSEL:
			break;
		case PLAYER_ID::KOMUK:
			mugen_engine::MECore::GetIns().LoadDivGraph("player", L"media/graphic/player/komuk.png", 4, 4);
			break;
		case PLAYER_ID::AKIYO:
			break;
		case PLAYER_ID::OBORO:
			break;
		}

		m_playerImg = &mugen_engine::MECore::GetIns().GetGraph("player");
	}

	/**********************************************************************//**
		@brief			�����X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRPlayer::Update()
	{
		m_transform.Update();
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRPlayer::Render() const
	{
		m_playerImg->DrawRotaGraph2X(static_cast<int>(m_transform.GetX()), static_cast<int>(m_transform.GetY()), 1.0f, 0.0f, 0.0f, 0);
	}
}