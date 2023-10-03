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
		m_graphicDevice.Initialize();
		m_graphicCommandList.Initialize(m_graphicDevice.GetDevice());
		m_renderTarget.Initialize(m_graphicDevice, m_graphicCommandList.GetCommandQueue(),
			m_windowHandle, window_width, window_height);
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

		m_renderTarget.SetBarrierBeforeRender(m_graphicCommandList.GetCommandList());

		return 0;
	}

	/**********************************************************************//**
		@brief			描画結果を画面に反映する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MECore::ScreenFlip()
	{
		m_renderTarget.SetBarrierBeforePresent(m_graphicCommandList.GetCommandList());
		m_graphicCommandList.Execute();
		m_renderTarget.Present();
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MECore::MECore() : m_windowClass {}, m_windowHandle(), m_windowWidth(0), m_windowHeight(0)
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

		ShowWindow( m_windowHandle, SW_SHOW);
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
