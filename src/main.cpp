//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"
#include "Engine/Input/KeyInputManager.h"

#include "Map/MapData.h"
#include "Mover/Player/Player.h"
#include "util/InputManager.h"
#include "util/Camera.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;

	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::Fps fps;

	mugen_engine::MECore::GetIns().LoadFont("gothic", L"ノスタルドット（M+）", 64);

	auto gothicFont = mugen_engine::MECore::GetIns().GetFont("gothic");
	auto defFont = mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");

	auto random = std::random_device();
	magica_rogue::MRMapData mapData(256, 256, random());

	int frame = 0;
	enum KeyCode {
		ME_INPUT_RIGHT, ME_INPUT_DOWN, ME_INPUT_LEFT, ME_INPUT_UP,
	};
	
	magica_rogue::MRCamera camera(0, 0);

	magica_rogue::MRPlayer player(magica_rogue::MRPlayer::PLAYER_ID::KOMUK, mapData.GetStartX(), mapData.GetStartY(), camera);

	while (mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MEKeyInputManager::GetIns().Update();
		magica_rogue::MRInputManager::GetIns().Update();

		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);
		
		player.Update();
		mapData.HitWithWall(player.GetTransform(), player.GetSize());
		player.Move();

		mapData.Render(camera);
		mapData.RenderMiniMap(player.GetTransform());
		player.Render();

		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		defFont.DrawFormatString(200, 720 - 32, color, -99.0, L"frame: %d", frame);
		fps.Draw();
		mugen_engine::MECore::GetIns().ScreenFlip();
		fps.Update();
		fps.Wait();

		frame++;
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}