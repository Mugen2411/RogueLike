//! @file Player.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Player.h"
#include "../../Engine/Core.h"
#include "../../util/InputManager.h"
#include "../../util/Constants.h"

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
		m_id(id), m_transform(x, y, 0.0f, 0.0f), m_camera(camera), m_size(16.0f)
	{
		switch (id)
		{
		case PLAYER_ID::AKARI:
			m_speed = 2.8f;
			break;
		case PLAYER_ID::MAMI:
			m_speed = 2.5f;
			break;
		case PLAYER_ID::YUKINA:
			m_speed = 2.2f;
			break;
		case PLAYER_ID::REEZE:
			m_speed = 3.2f;
			break;
		case PLAYER_ID::IOS:
			m_speed = 2.4f;
			break;
		case PLAYER_ID::ISHIKI:
			m_speed = 2.4f;
			break;
		case PLAYER_ID::HARUNA:
			m_speed = 3.5f;
			break;
		case PLAYER_ID::MISATO:
			m_speed = 2.4f;
			break;
		case PLAYER_ID::SSEL:
			m_speed = 2.7f;
			break;
		case PLAYER_ID::KOMUK:
			mugen_engine::MECore::GetIns().LoadDivGraph("player", L"media/graphic/player/komuk.png", 4, 4);
			m_speed = 3.0f;
			break;
		case PLAYER_ID::AKIYO:
			m_speed = 3.0f;
			break;
		case PLAYER_ID::OBORO:
			m_speed = 2.8f;
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
			vx += m_speed;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::LEFT) > 0)
		{
			vx -= m_speed;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::DOWN) > 0)
		{
			vy += m_speed;
			++numPushedButton;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::UP) > 0)
		{
			vy -= m_speed;
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
		m_camera.SetAnchor(static_cast<int>(m_transform.GetX() - constants::screen::left_margin - constants::screen::width / 2),
			static_cast<int>(m_transform.GetY() - constants::screen::height / 2));
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Render() const
	{
		m_playerImg->DrawRotaGraph2X(m_camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_camera.GetAnchoredY(static_cast<int>(m_transform.GetY())), 1.0f, 0.0f, constants::render_priority::player, 0);
	}
}