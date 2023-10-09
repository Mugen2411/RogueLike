//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"
#include "Graphic/GraphicRenderTarget.h"
#include "Graphic/GraphicPipeline.h"
#include "Graphic/GraphicGpuResourceManager.h"
#include "Graphic/GraphicLoadedImage.h"
#include "Graphic/GraphicFontData.h"

#include <DirectXMath.h>
#include <unordered_map>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MECore
		@brief		���f�B�A�T�|�[�g�G���W���̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MECore
	{
	public:
		//! �C���X�^���X�̎擾
		static MECore& GetIns();
		//! �ŏ��ɕK���Ăяo������������
		void Initialize(const std::wstring window_title, int window_width, int window_height);
		//! �Ō�ɕK���Ăяo���I������
		void Finalize();
		//! �V�X�e���̃��b�Z�[�W����������
		int ProcessMessage();
		//! �`�挋�ʂ���ʂɔ��f������
		void ScreenFlip();
		//! ��ʂ��w�肵���F�ŏ���������
		void ClearScreen(const int R, const int G, const int B);
		//! �`��\�Ȕ͈͂�ݒ肷��
		void SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY);
		//! �`��\�Ȕ͈͂���ʑS�̂ɐݒ肷��
		void ResetRenderArea();
		//! �摜���t�@�C������ǂݍ���
		void LoadGraph(std::string gid, std::wstring filepath);
		//! �摜���t�@�C�����番�����ēǂݍ���
		void LoadDivGraph(std::string gid, std::wstring filepath, size_t xDivideNum, size_t yDivideNum);
		//! �ǂݍ��ݍς݉摜���擾����
		MEGraphicLoadedImage& GetGraph(std::string gid);
		//! �t�H���g��ǂݍ���
		void LoadFont(std::string gid, std::wstring fontName, int fontSize);
		//! �ǂݍ��ݍς݃t�H���g���擾����
		MEGraphicFontData& GetFont(std::string gid);
		//! ��ʂ̉������擾
		int GetWindowWidth() const
		{
			return m_windowWidth;
		}
		//! ��ʂ̍������擾
		int GetWindowHeight() const
		{
			return m_windowHeight;
		}

	private:
		//! �f�t�H���g�R���X�g���N�^
		MECore();
		//! �R�s�[�R���X�g���N�^(�폜)
		MECore(const MECore&) = delete;

		//! �E�B���h�E�̍쐬
		void _CreateWindow();
		
		HWND m_windowHandle;											//!< �E�B���h�E�n���h��
		std::wstring m_windowTitle;										//!< �E�B���h�E�̖��O(�E�B���h�E�N���X�̖��O)
		WNDCLASSEX m_windowClass;										//!< �E�B���h�E�N���X
		int m_windowWidth;												//!< �E�B���h�E�̉���
		int m_windowHeight;												//!< �E�B���h�E�̍���

		D3D12_INPUT_ELEMENT_DESC m_inputLayout[2];						//!< ���̓��C�A�E�g

		MEGraphicDevice m_device;										//!< �O���t�B�b�N�f�o�C�X
		MEGraphicCommandList m_commandList;								//!< �O���t�B�b�N�R�}���h���X�g
		MEGraphicRenderTarget m_renderTarget;							//!< �����_�[�^�[�Q�b�g
		MEGraphicPipeline m_pipeline;									//!< �p�C�v���C��
		MEGraphicGpuResourceManager m_resourceManager;					//!< GPU���\�[�X�}�l�[�W���[

		std::unordered_map<std::string, MEGraphicLoadedImage> m_loadedImages;	//!< �ǂݍ��ݍς݉摜�������ŊǗ�����
		std::unordered_map<std::string, MEGraphicFontData> m_loadedFonts;		//!< �ǂݍ��ݍς݂̃t�H���g�������ŊǗ�����
	};
}

#endif//__MugenEngine_Core__