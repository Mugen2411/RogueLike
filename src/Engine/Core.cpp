#include "Core.h"
//! @file Core.cpp
//! @note Copyright (c) Mugen_GameLab

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			インスタンスの取得
		@param			なし
		@return			インスタンス
	*//***********************************************************************/
	MECore& MECore::GetIns()
	{
		static MECore instance;
		return instance;
	}
	/**********************************************************************//**
		@brief			初期化
		@param[in]		window_width		ウィンドウ(描画範囲)の横幅
		@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
		@return			インスタンス
	*//***********************************************************************/
	void MECore::Initialize(const std::wstring window_title, const int window_width, const int window_height)
	{
		m_windowWidth = window_width;
		m_windowHeight = window_height;
		m_windowTitle = window_title;
		_CreateWindow();
		m_device.Initialize();
		m_commandList.Initialize(m_device);
		m_renderTarget.Initialize(m_device, m_commandList,
			m_windowHandle, window_width, window_height);
		m_pipeline.Initialize(m_device, m_inputLayout, _countof(m_inputLayout));
		m_resourceManager.Initialize(m_device);
	}

	/**********************************************************************//**
		@brief			終了処理
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MECore::Finalize()
	{
		UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
	}

	/**********************************************************************//**
		@brief			システムのメッセージを処理する
		@param			なし
		@return			何もなければ0、アプリケーションが終了するなら-1
	*//***********************************************************************/
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

		m_renderTarget.SetBarrierBeforeRender(m_device, m_commandList);

		return 0;
	}

	/**********************************************************************//**
		@brief			描画結果を画面に反映する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MECore::ScreenFlip()
	{
		m_renderTarget.SetBarrierBeforePresent(m_commandList);
		m_commandList.Execute();
		m_renderTarget.Present();
	}

	/**********************************************************************//**
		@brief			画面を指定した色でクリアする
		@param[in]		R			赤の輝度
		@param[in]		G			緑の輝度
		@param[in]		B			青の輝度
		@return			なし
	*//***********************************************************************/
	void MECore::ClearScreen(const int R, const int G, const int B)
	{
		float clearColor[] = { R / 255.0f, G / 255.0f, B / 255.0f, 1.0f };
		m_renderTarget.Clear(clearColor, m_commandList);
	}

	/**********************************************************************//**
		@brief			描画可能な範囲を設定する
		@param[in]		topX		左上のX座標
		@param[in]		topY		左上のY座標
		@param[in]		bottomX		右下のX座標
		@param[in]		bottomY		右下のY座標
		@return			なし
	*//***********************************************************************/
	void MECore::SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY)
	{
		m_renderTarget.SetRenderArea(m_commandList, topX, topY, bottomX, bottomY);
	}
	/**********************************************************************//**
		@brief			描画可能な範囲を画面全体に設定する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MECore::ResetRenderArea()
	{
		SetRenderArea(0, 0, m_windowWidth, m_windowHeight);
	}

	void MECore::LoadGraph(std::string gid, std::wstring filepath)
	{
		auto img = m_resourceManager.LoadGraph(filepath, m_device, m_commandList, m_pipeline);
		m_loadedImageIndices[gid] = img;
	}

	MEGraphicLoadedImage& MECore::GetGraph(std::string gid)
	{
		return m_loadedImageIndices[gid];
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MECore::MECore() : m_windowClass {}, m_windowHandle(), m_windowWidth(0), m_windowHeight(0), m_inputLayout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	}
	{}

	/**********************************************************************//**
		@brief			ウィンドウの作成
		@param[in]		window_width		ウィンドウ(描画範囲)の横幅
		@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
		@return			なし
	*//***********************************************************************/
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
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
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
static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
