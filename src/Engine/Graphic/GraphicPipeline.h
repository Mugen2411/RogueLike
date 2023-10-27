//! @file GraphicPipeline.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicPipeline__
#define __MugenEngine_GraphicPipeline__

#include "GraphicDevice.h"

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicPipeline
		@brief		�u�����h�����܂ރp�C�v���C�����Ǘ�����N���X
	*//***********************************************************************/
	class MEGraphicPipeline
	{
	public: 
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEGraphicPipeline();

		/**********************************************************************//**
			@brief			������
			@param[in]		device			�f�o�C�X
			@param[in]		inputLayout			���̓��C�A�E�g
			@param[in]		layoutSize			���C�A�E�g�̃T�C�Y
			@return			�Ȃ�
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);

		/**********************************************************************//**
			@brief			�p�C�v���C���X�e�[�g�̐ݒ�
			@param[in]		type				�`��^�C�v(0=���߁E1=���Z�E2=���Z)
			@param			cmdList				�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void SetPipelineState(const int type, MEGraphicCommandList& cmdList);

	private:
		/**********************************************************************//**
			@brief			�o�C�g�R�[�h����̃G���[����
			@param[in]		result				�ǂݍ��ݎ��̃G���[�R�[�h
			@return			�Ȃ�
		*//***********************************************************************/
		void _ProcessBlobError(const HRESULT result);
		
		/**********************************************************************//**
			@brief			���[�g�V�O�l�`���̍쐬
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void _CreateRootSignarure(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�V�F�[�_�[�̓ǂݍ���
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _LoadShader();

		/**********************************************************************//**
			@brief			�p�C�v���C���X�e�[�g�̍쐬
			@param[in]		device				�f�o�C�X
			@param[in]		inputLayout			���̓��C�A�E�g
			@param[in]		layoutSize			���C�A�E�g�̃T�C�Y
			@return			�Ȃ�
		*//***********************************************************************/
		void _CreatePipelineState(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);

		std::vector<char> m_vsBlob;													//!< ���_�V�F�[�_�[�̃o�C�g�R�[�h
		std::vector<char> m_psBlob;													//!< �s�N�Z���V�F�[�_�[�̃o�C�g�R�[�h
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorBlob = nullptr;						//!< �o�C�g�R�[�h�ǂݍ��݂̃G���[�R�[�h

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState[3] = { nullptr };		//!< �p�C�v���C���X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;		//!< ���[�g�V�O�l�`��
	};
}

#endif//__MugenEngine_GraphicPipeline__