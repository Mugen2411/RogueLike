//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"
#include "Engine/Input/KeyInputManager.h"
#include "Util/InputManager.h"

#include "Scene/SceneMain.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;

	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::Fps fps;

	mugen_engine::MECore::GetIns().LoadFont("gothic", L"ノスタルドット（M+）", 64);
	mugen_engine::MECore::GetIns().LoadDivGraph("treasureBox", L"media/graphic/mapchip/treasureBox.png", 4, 1);

	auto gothicFont = mugen_engine::MECore::GetIns().GetFont("gothic");
	auto defFont = mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");

	int frame = 0;

	magica_rogue::MRSceneMain mainScene(nullptr);

	while (mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MEKeyInputManager::GetIns().Update();
		magica_rogue::MRInputManager::GetIns().Update();

		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);

		mainScene.Update();
		mainScene.Render();

		//float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//defFont.DrawFormatString(200, 720 - 32, color, -99.0, L"frame: %d", frame);
		fps.Draw();
		mugen_engine::MECore::GetIns().ScreenFlip();
		fps.Update();
		fps.Wait();

		frame++;
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}