//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"

#include "Map/MapData.h"

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
	magica_rogue::MRMapData mapData(720 / 8, 720 / 8, random());

	int frame = 0;
	while (mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);
		
		mapData.Render(0, 0);

		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		defFont.DrawFormatString(100, 720 - 32, color, -99.0, L"frame: %d", frame);
		fps.Draw();
		mugen_engine::MECore::GetIns().ScreenFlip();
		fps.Update();
		fps.Wait();

		frame++;
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}