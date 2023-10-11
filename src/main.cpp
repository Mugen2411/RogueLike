//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	
	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::Fps fps;

	mugen_engine::MECore::GetIns().LoadDivGraph("material", L"media/graphic/material.png", 4, 3);
	mugen_engine::MECore::GetIns().LoadGraph("esc", L"media/graphic/return_to_escape.png");

	mugen_engine::MECore::GetIns().LoadFont("gothic", L"ノスタルドット（M+）", 64);

	auto escGraph = mugen_engine::MECore::GetIns().GetGraph("esc");
	auto materialGraph = mugen_engine::MECore::GetIns().GetGraph("material");
	materialGraph.SetBlendType(mugen_engine::MEGraphicLoadedImage::ALPHA);
	auto gothicFont = mugen_engine::MECore::GetIns().GetFont("gothic");

	int frame = 0;
	while(mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);

		for(int i = 0; i < 30; i++)
		{
			escGraph.DrawRotaGraph(i * 32, i * 18, 0.5f+0.2f*i, 3.1415926f / 15 * i, 0.1f);
		}
		materialGraph.SetBrightness(1.0f, 1.0f, 1.0f, 0.05f);
		for(int i = 0; i < 5000; i++)
		{	
			materialGraph.DrawRotaGraph(10 + rand() % 1260, 10 + rand() % 700, (rand() % 10 + 10) / 10.0f, 3.1415926f / 120.0f * (rand() % 120), 0.2f, rand() % 12);
		}
		materialGraph.SetBrightness(1.0f, 1.0f, 1.0f, 1.0f);
		for(int i = 0; i < 5000; i++)
		{
			materialGraph.DrawRotaGraph(10 + rand() % 1260, 10 + rand() % 700, (rand() % 10 + 10) / 10.0f, 3.1415926f / 120.0f * (rand() % 120), 0.3f, rand() % 12);
		}
		float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		gothicFont.DrawFormatString(0, 720 - 128, color, -99.0, L"frame: %d", frame);
		fps.Draw();
		mugen_engine::MECore::GetIns().ScreenFlip();
		fps.Update();
		fps.Wait();

		frame++;
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}