//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"

constexpr int mapW = 12;
constexpr int mapH = 9;

int map[mapH][mapW] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,1,1,1},
	{1,0,0,0,1,1,1,1,0,1,1,1},
	{1,1,0,1,1,0,0,0,0,0,0,1},
	{1,1,0,1,1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};

int mapchip[mapH][mapW] = { 0 };

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;

	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::Fps fps;

	mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins.png", 8, 3);

	mugen_engine::MECore::GetIns().LoadFont("gothic", L"ノスタルドット（M+）", 64);

	auto gothicFont = mugen_engine::MECore::GetIns().GetFont("gothic");
	auto mapchipGraph = mugen_engine::MECore::GetIns().GetGraph("mapchip");

	for (int y = 0; y < mapH; ++y)
	{
		for (int x = 0; x < mapW; ++x)
		{
			int i = 0;
			if (map[y][x] == 0)
			{
				if (x != mapW - 1 && map[y][x + 1])
				{
					i |= 1;
				}
				if (y != mapH - 1 && map[y + 1][x])
				{
					i |= 2;
				}
				if (x != 0 && map[y][x - 1])
				{
					i |= 4;
				}
				if (y != 0 && map[y - 1][x])
				{
					i |= 8;
				}
			}
			else
			{
				i = 16;
			}
			
			mapchip[y][x] = i;
		}
	}

	int frame = 0;
	while (mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);

		for (int y = 0; y < mapH; ++y)
		{
			for (int x = 0; x < mapW; ++x)
			{
				mapchipGraph.DrawRotaGraph(120 + 64 * x, 120 + 64 * y, 2.0f, 0.0f, 0.0f, mapchip[y][x]);
			}
		}
		
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
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