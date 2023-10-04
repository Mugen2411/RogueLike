//! @file Core.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_Core__
#define __MugenEngine_Core__

#include "Graphic/GraphicDevice.h"
#include "Graphic/GraphicCommandList.h"
#include "Graphic/GraphicRenderTarget.h"
#include "Graphic/GraphicPipeline.h"

#include <DirectXMath.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MECore
		@brief		���f�B�A�T�|�[�g�G���W���̒��j�ƂȂ�N���X
	*//***********************************************************************/
	class MECore
	{
	public:
		/**********************************************************************//**
			@struct		VERTEX_DATA
			@brief		���_�P�ʂ̃f�[�^�Q
		*//***********************************************************************/
		struct VERTEX_DATA
		{
			DirectX::XMFLOAT3 pos;									//!< ���_�̍��W
			DirectX::XMFLOAT2 uv;									//!< �e�N�X�`����UV���W
		};

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

		D3D12_INPUT_ELEMENT_DESC m_inputLayout[2];						//!< ���̓��C�A�E�g

		MEGraphicDevice m_device;									//!< �O���t�B�b�N�f�o�C�X
		MEGraphicCommandList m_commandList;							//!< �O���t�B�b�N�R�}���h���X�g
		MEGraphicRenderTarget m_renderTarget;						//!< �����_�[�^�[�Q�b�g
		MEGraphicPipeline m_pipeline;								//!< �p�C�v���C��
	};
}

#endif//__MugenEngine_Core__