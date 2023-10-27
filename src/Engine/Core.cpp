//! @file Core.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Core.h"
#include "Graphic/GraphicRenderQueue.h"
#include "Input/KeyInputManager.h"

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace mugen_engine
{
	void MECore::Initialize(const std::wstring window_title, const int window_width, const int window_height)
	{
		m_windowWidth = window_width;
		m_windowHeight = window_height;
		m_windowTitle = window_title;
		_CreateWindow();
		m_graphicDevice.Initialize();
		m_commandList.Initialize(m_graphicDevice);
		m_renderTarget.Initialize(m_graphicDevice, m_commandList,
			m_windowHandle, window_width, window_height);
		m_pipeline.Initialize(m_graphicDevice, m_inputLayout, _countof(m_inputLayout));
		MEGraphicRenderQueue::Initialize(m_graphicDevice);
		MEKeyInputManager::GetIns().Initialize(m_windowHandle);

		m_audioDevice.Initialize();

		LoadFont("__mugen_engine_default__", L"ＭＳ ゴシック", 32);
	}

	void MECore::Finalize()
	{
		UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
	}

	int MECore::ProcessMessage()
	{
		MSG msg = {};

		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			return -1;
		}

		m_renderTarget.SetBarrierBeforeRender(m_graphicDevice, m_commandList);

		return 0;
	}

	void MECore::ScreenFlip()
	{
		MEGraphicRenderQueue::RenderAll(m_commandList, m_pipeline, m_renderTarget);
		m_renderTarget.SetBarrierBeforePresent(m_commandList);
		m_commandList.Execute();
		m_renderTarget.Present();

		for (auto& i : m_loadedImages)
		{
			i.second.ResetAdditionalVertexBuffer();
		}
	}

	void MECore::ClearScreen(const int R, const int G, const int B)
	{
		float clearColor[] = { R / 255.0f, G / 255.0f, B / 255.0f, 1.0f };
		m_renderTarget.Clear(clearColor, m_commandList);
	}

	void MECore::SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY)
	{
		m_renderTarget.SetRenderArea(m_commandList, topX, topY, bottomX, bottomY);
	}

	void MECore::ResetRenderArea()
	{
		SetRenderArea(0, 0, m_windowWidth, m_windowHeight);
	}

	void MECore::LoadGraph(const std::string gid, const std::wstring filepath)
	{
		auto img = MEImage(filepath, m_graphicDevice, 1, 1, m_commandList, m_pipeline, m_renderTarget);
		m_loadedImages[gid] = img;
	}

	void MECore::LoadDivGraph(const std::string gid, const std::wstring filepath, const size_t xDivideNum, const size_t yDivideNum)
	{
		auto img = MEImage(filepath, m_graphicDevice, xDivideNum, yDivideNum, m_commandList, m_pipeline, m_renderTarget);
		m_loadedImages[gid] = img;
	}

	MEImage& MECore::GetGraph(const std::string gid)
	{
		return m_loadedImages[gid];
	}

	void MECore::LoadFont(const std::string gid, const std::wstring fontName, const int fontSize)
	{
		//if (m_loadedFonts.find(gid) != m_loadedFonts.end()) return;
		m_loadedFonts[gid] = MEFontData(fontName, fontSize, m_graphicDevice, m_commandList, m_pipeline, m_renderTarget);
	}

	MEFontData& MECore::GetFont(const std::string gid)
	{
		return m_loadedFonts[gid];
	}

	MECore::MECore() : m_windowClass {}, m_windowHandle(), m_windowWidth(0), m_windowHeight(0), m_inputLayout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	}
	{}

	void MECore::_CreateWindow()
	{
		m_windowClass.cbSize = sizeof(m_windowClass);
		m_windowClass.lpfnWndProc = WindowProcedure;
		m_windowClass.lpszClassName = m_windowTitle.c_str();
		m_windowClass.hInstance = GetModuleHandle(nullptr);

		RegisterClassEx(&m_windowClass);

		RECT wrc = { 0, 0, m_windowWidth, m_windowHeight };
		AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

		m_windowHandle = CreateWindow(m_windowClass.lpszClassName, m_windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
			wrc.right - wrc.left, wrc.bottom - wrc.top,
			nullptr, nullptr, m_windowClass.hInstance, nullptr);

		ShowWindow(m_windowHandle, SW_SHOW);
	}
}

/**
 *****************************************************************************
 * @brief	ウィンドウプロシージャ
 * @param	hwnd ウィンドウハンドル
 * @param	msg	メッセージ
 * @param	wparam	パラメータ
 * @param	lparam	パラメータ
 * @retval 0 正常終了
 * @retval 継続
 * @details
 *****************************************************************************
 */
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
