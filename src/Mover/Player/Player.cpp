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
	MRPlayer::MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera) :
		m_id(id), m_transform(x, y, 0.0f, 0.0f), m_camera(camera), m_size(16.0f), m_hp(10.0f), MRStateMachine(this)
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
			mugen_engine::MECore::GetIns().LoadDivGraph("player", L"media/graphic/player/komuk.png", 8, 2);
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

		mugen_engine::MECore::GetIns().LoadDivGraph("hpGuage", L"media/graphic/UI/HPGuage.png", 1, 9);
		m_hpGuageImg = &mugen_engine::MECore::GetIns().GetGraph("hpGuage");

		mugen_engine::MECore::GetIns().LoadFont("guageNumber", L"ＭＳ ゴシック", 16);
		m_guageFont = &mugen_engine::MECore::GetIns().GetFont("guageNumber");

		UpdateRegister(static_cast<int>(STATE::STAND), &MRPlayer::UpdateOnStand);
		RenderRegister(static_cast<int>(STATE::STAND), &MRPlayer::RenderOnStand);
		UpdateRegister(static_cast<int>(STATE::KNOCKBACKED), &MRPlayer::UpdateOnKnockbacked);
		RenderRegister(static_cast<int>(STATE::KNOCKBACKED), &MRPlayer::RenderOnKnockbacked);
		ChangeState(static_cast<int>(STATE::STAND));
	}

	/**********************************************************************//**
		@brief			情報を更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Update()
	{
		MRStateMachine::Update();
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
		MRStateMachine::Render();
		for (int i = 0; i < 4; ++i)
		{
			m_hpGuageImg->DrawRotaGraph2X(64, 8 + 32 * i + constants::screen::left_margin, 1.0f, 0.0f,
				constants::render_priority::UI_GUAGE_FRAME, 0);
		}

		constexpr int guageMargin = 4;
		constexpr int guageWidth = 120;
		constexpr int guageHeight = 8;

		constexpr int hpGuageTopX = guageMargin;
		constexpr int hpGuageTopY = constants::screen::left_margin + guageMargin;
		// HPゲージの描画
		m_hpGuageImg->DrawModiGraph2X(hpGuageTopX + static_cast<int>(guageWidth * m_hp.GetRatio()), hpGuageTopY,
			hpGuageTopX + static_cast<int>(guageWidth * m_hp.GetRatio()), hpGuageTopY + guageHeight,
			hpGuageTopX, hpGuageTopY,
			hpGuageTopX, hpGuageTopY + guageHeight,
			constants::render_priority::UI_GUAGE_MAIN, 1);
		m_hpGuageImg->DrawModiGraph2X(hpGuageTopX + guageWidth, hpGuageTopY,
			hpGuageTopX + guageWidth, hpGuageTopY + guageHeight,
			hpGuageTopX, hpGuageTopY,
			hpGuageTopX, hpGuageTopY + guageHeight,
			constants::render_priority::UI_GUAGE_BASE, 2);
		const float fontColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_guageFont->DrawFormatString(0, constants::screen::left_margin * 2 + 32,
			fontColor, constants::render_priority::UI_GUAGE_NUMBER, L"HP: %.1f / %.1f", m_hp.GetValue(), m_hp.GetMax());
	}

	/**********************************************************************//**
		@brief			立ち状態での更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::UpdateOnStand()
	{
		auto input = MRInputManager::GetIns();
		int numPushedButton = 0;
		float vx = 0.0f;
		float vy = 0.0f;
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::RIGHT) > 0)
		{
			vx += m_speed;
			++numPushedButton;
			m_isLeft = false;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::LEFT) > 0)
		{
			vx -= m_speed;
			++numPushedButton;
			m_isLeft = true;
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
			m_currentAnimation = 0.0f;
		}
		else
		{
			m_transform.SetVelocity(vx / std::sqrtf(static_cast<float>(numPushedButton)),
				vy / std::sqrtf(static_cast<float>(numPushedButton)));
			m_currentAnimation += 0.1f;
			if (m_currentAnimation > 4.0f) m_currentAnimation -= 4.0f;
		}
		if (input.GetPushedFrame(MRInputManager::MRKeyCode::MENU) == 1)
		{
			m_frameCount = 0;
			m_hp.Damage(0.3f);
			m_transform.SetVelocityWithAngle(6.28f * (rand() % 16) / 16.0f, 4.0f);
			ChangeState(static_cast<int>(STATE::KNOCKBACKED));
			return;
		}
	}

	/**********************************************************************//**
		@brief			立ち状態での描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::RenderOnStand() const
	{
		m_playerImg->DrawRotaGraph2X(m_camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_camera.GetAnchoredY(static_cast<int>(m_transform.GetY())), 1.0f, 0.0f, constants::render_priority::PLAYER,
			static_cast<int>(m_currentAnimation) + m_isLeft * 8);
	}

	/**********************************************************************//**
		@brief			のけぞり状態での更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::UpdateOnKnockbacked()
	{
		if (m_transform.GetVelocityX() > 0.1f)
		{
			m_isLeft = false;
		}
		else if (m_transform.GetVelocityX() < -0.1f)
		{
			m_isLeft = true;
		}

		if (m_frameCount > 10)
		{
			m_frameCount = 0;
			ChangeState(static_cast<int>(STATE::STAND));
		}
		++m_frameCount;
	}

	/**********************************************************************//**
		@brief			のけぞり状態での描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::RenderOnKnockbacked() const
	{
		if (m_frameCount % 3 == 0)
		{
			m_playerImg->SetBrightness(1.0f, 0.0f, 0.0f, 1.0f);
		}
		m_playerImg->DrawRotaGraph2X(m_camera.GetAnchoredX(static_cast<int>(m_transform.GetX())),
			m_camera.GetAnchoredY(static_cast<int>(m_transform.GetY())), 1.0f, 0.0f, constants::render_priority::PLAYER,
			6 + m_isLeft * 8);
		m_playerImg->SetBrightness(1.0f, 1.0f, 1.0f, 1.0f);
	}
}