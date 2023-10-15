//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab
#include "Engine/Core.h"
#include "Engine/Fps.h"
#include "Engine/Input/KeyInputManager.h"

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
	magica_rogue::MRMapData mapData(256, 256, random());

	int frame = 0;
	enum KeyCode {
		ME_INPUT_RIGHT, ME_INPUT_DOWN, ME_INPUT_LEFT, ME_INPUT_UP,
	};
	mugen_engine::MEKeyInputManager::GetIns().AddKeycode(ME_INPUT_RIGHT, 'D',
		mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLR, XINPUT_GAMEPAD_DPAD_RIGHT);
	mugen_engine::MEKeyInputManager::GetIns().AddKeycode(ME_INPUT_DOWN, 'S',
		mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLD, XINPUT_GAMEPAD_DPAD_DOWN);
	mugen_engine::MEKeyInputManager::GetIns().AddKeycode(ME_INPUT_LEFT, 'A',
		mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLL, XINPUT_GAMEPAD_DPAD_LEFT);
	mugen_engine::MEKeyInputManager::GetIns().AddKeycode(ME_INPUT_UP, 'W',
		mugen_engine::MEKeyInputManager::GAMEPAD_KEYTYPE::ThumbLU, XINPUT_GAMEPAD_DPAD_UP);

	int cameraX = 0;
	int cameraY = 0;
	while (mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MEKeyInputManager::GetIns().Update();

		if (mugen_engine::MEKeyInputManager::GetIns().GetKey(ME_INPUT_RIGHT) & 0b011)
		{
			cameraX += 8;
		}
		if (mugen_engine::MEKeyInputManager::GetIns().GetKey(ME_INPUT_DOWN) & 0b011)
		{
			cameraY += 8;
		}
		if (mugen_engine::MEKeyInputManager::GetIns().GetKey(ME_INPUT_LEFT) & 0b011)
		{
			cameraX -= 8;
		}
		if (mugen_engine::MEKeyInputManager::GetIns().GetKey(ME_INPUT_UP) & 0b011)
		{
			cameraY -= 8;
		}

		mugen_engine::MECore::GetIns().ResetRenderArea();
		mugen_engine::MECore::GetIns().ClearScreen(0, 0, 0);
		
		mapData.Render(cameraX, cameraY);

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