//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	
	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::MECore::GetIns().LoadGraph("material", L"media/graphic/materials_x4.png");
	mugen_engine::MECore::GetIns().LoadGraph("esc", L"media/graphic/return_to_escape.png");

	while(mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0xFF, 0xFF);

		mugen_engine::MECore::GetIns().GetGraph("material").DrawGraph(640, 360);
		for(int i = 0; i < 30; i++)
		{
			mugen_engine::MECore::GetIns().GetGraph("esc").DrawRotaGraph(i * 32, i * 18, 0.5f+0.2f*i, 3.1415926f / 15 * i);
		}

		mugen_engine::MECore::GetIns().ScreenFlip();
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}