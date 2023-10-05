//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <memory>

#include <wrl/client.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3dx12.h>

#include "Engine/Core.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	
	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::MECore::GetIns().LoadGraph("esc", L"media/graphic/return_to_escape.png");

	while(mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0xFF, 0xFF);

		mugen_engine::MECore::GetIns().GetGraph("esc").DrawGraph(120, 120);

		mugen_engine::MECore::GetIns().ScreenFlip();
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}