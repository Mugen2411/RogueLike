//! @file Player.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Player.h"
#include "../../Engine/Core.h"
#include "../../util/InputManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		id						プレイヤーID
		@param[in]		x						X座標
		@param[in]		y						Y座標
		@return			なし
	*//***********************************************************************/
	MRPlayer::MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera):
		m_id(id), m_transform(x, y, 0.0f, 0.0f), m_camera(camera), m_size(14.0f)
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
		@brief			情報を更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Update()
	{
		auto input = MRInputManager::GetIns();
		int numPushedButton = 0;
		float vx = 0.0f;
		float vy = 0.0f;
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::RIGHT) > 0)
		{
			vx += 4.0f;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::LEFT) > 0)
		{
			vx -= 4.0f;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::DOWN) > 0)
		{
			vy += 4.0f;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::UP) > 0)
		{
			vy -= 4.0f;
			++numPushedButton;
		}
		if (numPushedButton == 0)
		{
			m_transform.SetVelocity(0.0f, 0.0f);
		}
		else
		{
			m_transform.SetVelocity(vx / std::sqrtf(static_cast<float>(numPushedButton)),
				vy / std::sqrtf(static_cast<float>(numPushedButton)));
		}
	}

	/**********************************************************************//**
		@brief			キャラを移動させる
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Move()
	{
		m_transform.Update();
		m_camera.SetAnchor(static_cast<int>(m_transform.GetX() - 320.0f), static_cast<int>(m_transform.GetY() - 180.0f));
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Render() const
	{
		m_playerImg->DrawRotaGraph2X(m_camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_camera.GetAnchoredY(static_cast<int>(m_transform.GetY())), 1.0f, 0.0f, 0.0f, 4);
	}
}