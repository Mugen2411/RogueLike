//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"
#include "Graphic/GraphicRenderTarget.h"

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

	private:
		//! �f�t�H���g�R���X�g���N�^
		MECore();
		//! �R�s�[�R���X�g���N�^(�폜)
		MECore(const MECore&) = delete;

		//! �E�B���h�E�̍쐬
		void _CreateWindow();
		
		HWND m_windowHandle;										//!< �E�B���h�E�n���h��
		std::wstring m_windowTitle;									//!< �E�B���h�E�̖��O(�E�B���h�E�N���X�̖��O)
		WNDCLASSEX m_windowClass;									//!< �E�B���h�E�N���X
		int m_windowWidth;											//!< �E�B���h�E�̉���
		int m_windowHeight;											//!< �E�B���h�E�̍���

		MEGraphicDevice m_graphicDevice;							//!< �O���t�B�b�N�f�o�C�X
		MEGraphicCommandList m_graphicCommandList;					//!< �O���t�B�b�N�R�}���h���X�g
		MEGraphicRenderTarget m_renderTarget;						//!< �����_�[�^�[�Q�b�g
	};
}

#endif//__MugenEngine_Core__