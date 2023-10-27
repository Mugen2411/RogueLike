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
	MRPlayer::MRPlayer(const PLAYER_ID id, const float x, const float y, MRCamera& camera) : MRMoverInterface(x, y, 14.0f, MRAliveState::ALIVE),
		m_id(id), m_camera(camera), m_hp(10.0f), m_mp(10.0f), m_frameCount(0),
		m_animator(0.1f, 4.0f), m_stateMachine(this)
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

		mugen_engine::MECore::GetIns().LoadDivGraph("aim", L"media/graphic/player/aim.png", 3, 1);
		m_aimImg = &mugen_engine::MECore::GetIns().GetGraph("aim");

		mugen_engine::MECore::GetIns().LoadFont("guageNumber", L"ＭＳ ゴシック", 16);
		m_guageFont = &mugen_engine::MECore::GetIns().GetFont("guageNumber");

		m_stateMachine.Register(static_cast<int>(STATE::STAND), &MRPlayer::UpdateOnStand, &MRPlayer::RenderOnStand);
		m_stateMachine.Register(static_cast<int>(STATE::KNOCKBACKED), &MRPlayer::UpdateOnKnockbacked, &MRPlayer::RenderOnKnockbacked);
		m_stateMachine.ChangeState(static_cast<int>(STATE::STAND));
	}

	/**********************************************************************//**
		@brief			情報を更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRMoverInterface::MRAliveState MRPlayer::Update()
	{
		m_stateMachine.Update();
		return m_aliveState;
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
		m_stateMachine.Render();
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
		m_guageFont->DrawFormatString(0, constants::screen::left_margin * 2 + 32 + 64 * 0,
			fontColor, constants::render_priority::UI_GUAGE_NUMBER, L"HP: %.1f / %.1f", m_hp.GetValue(), m_hp.GetMax());

		constexpr int mpGuageTopX = guageMargin;
		constexpr int mpGuageTopY = constants::screen::left_margin + guageMargin + 32;
		// MPゲージの描画
		m_hpGuageImg->DrawModiGraph2X(mpGuageTopX + static_cast<int>(guageWidth * m_mp.GetRatio()), mpGuageTopY,
			mpGuageTopX + static_cast<int>(guageWidth * m_mp.GetRatio()), mpGuageTopY + guageHeight,
			mpGuageTopX, mpGuageTopY,
			mpGuageTopX, mpGuageTopY + guageHeight,
			constants::render_priority::UI_GUAGE_MAIN, 3);
		m_hpGuageImg->DrawModiGraph2X(mpGuageTopX + guageWidth, mpGuageTopY,
			mpGuageTopX + guageWidth, mpGuageTopY + guageHeight,
			mpGuageTopX, mpGuageTopY,
			mpGuageTopX, mpGuageTopY + guageHeight,
			constants::render_priority::UI_GUAGE_BASE, 4);
		m_guageFont->DrawFormatString(0, constants::screen::left_margin * 2 + 32 + 64 * 1,
			fontColor, constants::render_priority::UI_GUAGE_NUMBER, L"MP: %.1f / %.1f", m_mp.GetValue(), m_mp.GetMax());

		// 照準の描画
		const int mouseX = MRInputManager::GetIns().GetMouseX();
		const int mouseY = MRInputManager::GetIns().GetMouseY();
		m_aimImg->DrawGraph2X(mouseX, mouseY,
			constants::render_priority::SYSTEM_AIM, 0);
		m_aimImg->DrawModiGraph2X(mouseX + 2, mouseY - 16, mouseX + 2, mouseY + 16, mouseX - 2, mouseY - 16, mouseX - 2, mouseY + 16,
			constants::render_priority::SYSTEM_AIM_GUAGE_BASE, 2);
		m_aimImg->DrawModiGraph2X(mouseX + 2, mouseY - 16, mouseX + 2, static_cast<int>(mouseY - 16 + 32 * m_mp.GetRatio()),
			mouseX - 2, mouseY - 16, mouseX - 2, static_cast<int>(mouseY - 16 + 32 * m_mp.GetRatio()),
			constants::render_priority::SYSTEM_AIM_GUAGE_MAIN, 1);
	}

	/**********************************************************************//**
		@brief			ダメージを食らう
		@param[in]			power					受ける素のダメージ
		@param[in]			knockback				吹き飛ばされる威力
		@param[in]			angle					吹き飛ばされる角度
		@param[in]			duration				吹き飛ばされる時間
		@return			なし
	*//***********************************************************************/
	void MRPlayer::Damage(const float power, const float knockback, const float angle, const int duration)
	{
		if (m_stateMachine.GetState() == static_cast<int>(STATE::KNOCKBACKED)) return;
		m_knockbackDuration = duration;
		m_hp.Damage(power);
		m_transform.SetVelocityWithAngle(angle, knockback);
		m_stateMachine.ChangeState(static_cast<int>(STATE::KNOCKBACKED));
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
			m_animator.Reset();
		}
		else
		{
			m_transform.SetVelocity(vx / std::sqrtf(static_cast<float>(numPushedButton)),
				vy / std::sqrtf(static_cast<float>(numPushedButton)));
			m_animator.Update();
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
			static_cast<int>(m_animator.Get()) + m_isLeft * 8);
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
			m_isLeft = true;
		}
		else if (m_transform.GetVelocityX() < -0.1f)
		{
			m_isLeft = false;
		}

		if (m_stateMachine.GetFrame() > m_knockbackDuration)
		{
			m_stateMachine.ChangeState(static_cast<int>(STATE::STAND));
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

	/**********************************************************************//**
		@brief			攻撃
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRPlayer::_Shot()
	{
		if (MRInputManager::GetIns().GetPushedFrame(MRInputManager::MRKeyCode::ATTACK1) % 5 == 0)
		{

		}
	}
}