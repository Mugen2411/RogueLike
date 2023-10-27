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

#include "Audio/AudioDevice.h"

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
		/**********************************************************************//**
			@brief			�C���X�^���X�̎擾
			@param			�Ȃ�
			@return			�C���X�^���X
		*//***********************************************************************/
		static MECore& GetIns()
		{
			static MECore instance;
			return instance;
		}

		/**********************************************************************//**
			@brief			������
			@param[in]		window_title		�E�B���h�E�̃^�C�g��
			@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
			@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
			@return			�C���X�^���X
		*//***********************************************************************/
		void Initialize(const std::wstring window_title, int window_width, int window_height);

		/**********************************************************************//**
			@brief			�I������
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Finalize();

		/**********************************************************************//**
			@brief			�V�X�e���̃��b�Z�[�W����������
			@param			�Ȃ�
			@return			�����Ȃ����0�A�A�v���P�[�V�������I������Ȃ�-1
		*//***********************************************************************/
		int ProcessMessage();

		/**********************************************************************//**
			@brief			�`�挋�ʂ���ʂɔ��f����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void ScreenFlip();

		/**********************************************************************//**
			@brief			��ʂ��w�肵���F�ŃN���A����
			@param[in]		R			�Ԃ̋P�x
			@param[in]		G			�΂̋P�x
			@param[in]		B			�̋P�x
			@return			�Ȃ�
		*//***********************************************************************/
		void ClearScreen(const int R, const int G, const int B);

		/**********************************************************************//**
			@brief			�`��\�Ȕ͈͂�ݒ肷��
			@param[in]		topX		�����X���W
			@param[in]		topY		�����Y���W
			@param[in]		bottomX		�E����X���W
			@param[in]		bottomY		�E����Y���W
			@return			�Ȃ�
		*//***********************************************************************/
		void SetRenderArea(const int topX, const int topY, const int bottomX, const int bottomY);

		/**********************************************************************//**
			@brief			�`��\�Ȕ͈͂���ʑS�̂ɐݒ肷��
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void ResetRenderArea();

		/**********************************************************************//**
			@brief			�t�@�C������摜��ǂݍ���
			@param[in]		gid				���o���L�[
			@param[in]		filepath		�摜�t�@�C���ւ̃p�X
			@return			�Ȃ�
		*//***********************************************************************/
		void LoadGraph(const std::string gid, const std::wstring filepath);

		/**********************************************************************//**
			@brief			�t�@�C�����番�����ĉ摜��ǂݍ���
			@param[in]		gid				���o���L�[
			@param[in]		filepath		�摜�t�@�C���ւ̃p�X
			@param[in]		xDivideNum		�������̕�����
			@param[in]		yDivideNum		�c�����̕�����
			@return			�Ȃ�
		*//***********************************************************************/
		void LoadDivGraph(const std::string gid, const std::wstring filepath, const size_t xDivideNum, const size_t yDivideNum);

		/**********************************************************************//**
			@brief			�L�[���w�肵�ēǂݍ��ݍς݉摜�����o��
			@param[in]		gid				���o���L�[
			@return			�ǂݍ��ݍς݉摜
		*//***********************************************************************/
		MEImage& GetGraph(const std::string gid);

		/**********************************************************************//**
			@brief			�t�H���g��ǂݍ���
			@param[in]		gid				���o���L�[
			@param[in]		fontName		�t�H���g�̖��O
			@param[in]		fontSize		�t�H���g�T�C�Y
			@return			�Ȃ�
		*//***********************************************************************/
		void LoadFont(const std::string gid, const std::wstring fontName, const int fontSize);

		/**********************************************************************//**
			@brief			�L�[���w�肵�ēǂݍ��݃t�H���g�����o��
			@param[in]		gid				���o���L�[
			@return			�ǂݍ��ݍς݃t�H���g
		*//***********************************************************************/
		MEFontData& GetFont(const std::string gid);

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
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MECore();

		//! �R�s�[�R���X�g���N�^(�폜)
		MECore(const MECore&) = delete;

		/**********************************************************************//**
			@brief			�E�B���h�E�̍쐬
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _CreateWindow();
		
		HWND m_windowHandle;											//!< �E�B���h�E�n���h��
		std::wstring m_windowTitle;										//!< �E�B���h�E�̖��O(�E�B���h�E�N���X�̖��O)
		WNDCLASSEX m_windowClass;										//!< �E�B���h�E�N���X
		int m_windowWidth;												//!< �E�B���h�E�̉���
		int m_windowHeight;												//!< �E�B���h�E�̍���

		D3D12_INPUT_ELEMENT_DESC m_inputLayout[2];						//!< ���̓��C�A�E�g

		MEGraphicDevice m_graphicDevice;										//!< �O���t�B�b�N�f�o�C�X
		MEGraphicCommandList m_commandList;								//!< �O���t�B�b�N�R�}���h���X�g
		MEGraphicRenderTarget m_renderTarget;							//!< �����_�[�^�[�Q�b�g
		MEGraphicPipeline m_pipeline;									//!< �p�C�v���C��

		MEAudioDevice m_audioDevice;									//!< �I�[�f�B�I�f�o�C�X

		std::unordered_map<std::string, MEImage> m_loadedImages;	//!< �ǂݍ��ݍς݉摜�������ŊǗ�����
		std::unordered_map<std::string, MEFontData> m_loadedFonts;		//!< �ǂݍ��ݍς݂̃t�H���g�������ŊǗ�����
	};
}

#endif//__MugenEngine_Core__