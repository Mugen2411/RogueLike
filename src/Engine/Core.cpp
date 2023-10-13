//! @file Core.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Core.h"
#include "Graphic/GraphicRenderQueue.h"

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�C���X�^���X�̎擾
		@param			�Ȃ�
		@return			�C���X�^���X
	*//***********************************************************************/
	MECore& MECore::GetIns()
	{
		static MECore instance;
		return instance;
	}
	/**********************************************************************//**
		@brief			������
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�C���X�^���X
	*//***********************************************************************/
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

		m_audioDevice.Initialize();

		LoadFont("__mugen_engine_default__", L"�l�r �S�V�b�N", 32);
	}

	/**********************************************************************//**
		@brief			�I������
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::Finalize()
	{
		UnregisterClass(m_windowClass.lpszClassName, m_windowClass.hInstance);
	}

	/**********************************************************************//**
		@brief			�V�X�e���̃��b�Z�[�W����������
		@param			�Ȃ�
		@return			�����Ȃ����0�A�A�v���P�[�V�������I������Ȃ�-1
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

		m_renderTarget.SetBarrierBeforeRender(m_graphicDevice, m_commandList);

		return 0;
	}

	/**********************************************************************//**
		@brief			�`�挋�ʂ���ʂɔ��f����
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::ScreenFlip()
	{
		MEGraphicRenderQueue::RenderAll(m_commandList, m_pipeline, m_renderTarget);
		m_renderTarget.SetBarrierBeforePresent(m_commandList);
		m_commandList.Execute();
		m_renderTarget.Present();
	}

	/**********************************************************************//**
		@brief			��ʂ��w�肵���F�ŃN���A����
		@param[in]		R			�Ԃ̋P�x
		@param[in]		G			�΂̋P�x
		@param[in]		B			�̋P�x
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::ClearScreen(const int R, const int G, const int B)
	{
		float clearColor[] = { R / 255.0f, G / 255.0f, B / 255.0f, 1.0f };
		m_renderTarget.Clear(clearColor, m_commandList);
	}

	/**********************************************************************//**
		@brief			�`��\�Ȕ͈͂�ݒ肷��
		@param[in]		topX		�����X���W
		@param[in]		topY		�����Y���W
		@param[in]		bottomX		�E����X���W
		@param[in]		bottomY		�E����Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY)
	{
		m_renderTarget.SetRenderArea(m_commandList, topX, topY, bottomX, bottomY);
	}

	/**********************************************************************//**
		@brief			�`��\�Ȕ͈͂���ʑS�̂ɐݒ肷��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::ResetRenderArea()
	{
		SetRenderArea(0, 0, m_windowWidth, m_windowHeight);
	}

	/**********************************************************************//**
		@brief			�t�@�C������摜��ǂݍ���
		@param[in]		gid				���o���L�[
		@param[in]		filepath		�摜�t�@�C���ւ̃p�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::LoadGraph(std::string gid, std::wstring filepath)
	{
		auto img = MEImage(filepath, m_graphicDevice, 1, 1, m_commandList, m_pipeline, m_renderTarget);
		m_loadedImages[gid] = img;
	}

	/**********************************************************************//**
		@brief			�t�@�C������摜��ǂݍ���
		@param[in]		gid				���o���L�[
		@param[in]		filepath		�摜�t�@�C���ւ̃p�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::LoadDivGraph(std::string gid, std::wstring filepath, size_t xDivideNum, size_t yDivideNum)
	{
		auto img = MEImage(filepath, m_graphicDevice, xDivideNum, yDivideNum, m_commandList, m_pipeline, m_renderTarget);
		m_loadedImages[gid] = img;
	}

	/**********************************************************************//**
		@brief			�L�[���w�肵�ēǂݍ��ݍς݉摜�����o��
		@param[in]		gid				���o���L�[
		@return			�ǂݍ��ݍς݉摜
	*//***********************************************************************/
	MEImage& MECore::GetGraph(std::string gid)
	{
		return m_loadedImages[gid];
	}

	/**********************************************************************//**
		@brief			�t�H���g��ǂݍ���
		@param[in]		gid				���o���L�[
		@param[in]		fontName		�t�H���g�̖��O
		@param[in]		fontSize		�t�H���g�T�C�Y
		@return			�Ȃ�
	*//***********************************************************************/
	void MECore::LoadFont(std::string gid, std::wstring fontName, int fontSize)
	{
		m_loadedFonts[gid] = MEFontData(fontName, fontSize, m_graphicDevice, m_commandList, m_pipeline, m_renderTarget);
	}

	/**********************************************************************//**
		@brief			�L�[���w�肵�ēǂݍ��݃t�H���g�����o��
		@param[in]		gid				���o���L�[
		@return			�ǂݍ��ݍς݃t�H���g
	*//***********************************************************************/
	MEFontData& MECore::GetFont(std::string gid)
	{
		return m_loadedFonts[gid];
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MECore::MECore() : m_windowClass {}, m_windowHandle(), m_windowWidth(0), m_windowHeight(0), m_inputLayout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	}
	{}

	/**********************************************************************//**
		@brief			�E�B���h�E�̍쐬
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�Ȃ�
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
 * @brief	�E�B���h�E�v���V�[�W��
 * @param	hwnd �E�B���h�E�n���h��
 * @param	msg	���b�Z�[�W
 * @param	wparam	�p�����[�^
 * @param	lparam	�p�����[�^
 * @retval 0 ����I��
 * @retval �p��
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
