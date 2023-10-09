//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	
	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::MECore::GetIns().LoadDivGraph("material", L"media/graphic/material.png", 4, 3);
	mugen_engine::MECore::GetIns().LoadGraph("esc", L"media/graphic/return_to_escape.png");

	mugen_engine::MECore::GetIns().LoadFont("gothic", L"�m�X�^���h�b�g�iM+�j", 64);

	auto escGraph = mugen_engine::MECore::GetIns().GetGraph("esc");
	auto materialGraph = mugen_engine::MECore::GetIns().GetGraph("material");
	materialGraph.SetBrightness(1.0f, 0.2f, 0.2f, 1.0f);
	auto gothicFont = mugen_engine::MECore::GetIns().GetFont("gothic");

	while(mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);

		for(int i = 0; i < 30; i++)
		{
			escGraph.DrawRotaGraph(i * 32, i * 18, 0.5f+0.2f*i, 3.1415926f / 15 * i);
		}

		for(int i = 0; i < 12; i++)
		{	
			materialGraph.DrawRotaGraph(64 + i * 96, 64 + i * 48, 1.0f + 0.4f * i, 3.1415926f / 12 * i, i);
		}
		float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		gothicFont.DrawString(60, 60, color , L"���Ȃ݂�\n���{���\n�������\n�ł���");

		mugen_engine::MECore::GetIns().ScreenFlip();
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}