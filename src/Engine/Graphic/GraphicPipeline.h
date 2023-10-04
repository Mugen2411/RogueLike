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
		//! �R���X�g���N�^
		MEGraphicPipeline();
		//! ������
		void Initialize(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);
	private:
		//! �o�C�g�R�[�h����̃G���[����
		void _ProcessBlobError(HRESULT result);
		//! ���[�g�V�O�l�`���̍쐬
		void _CreateRootSignarure(const MEGraphicDevice& device);
		//! �V�F�[�_�[�̓ǂݍ���
		void _LoadShader();
		//! �p�C�v���C���X�e�[�g�̍쐬
		void _CreatePipelineState(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);

		std::vector<char> m_vsBlob;													//!< ���_�V�F�[�_�[�̃o�C�g�R�[�h
		std::vector<char> m_psBlob;													//!< �s�N�Z���V�F�[�_�[�̃o�C�g�R�[�h
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorBlob = nullptr;						//!< �o�C�g�R�[�h�ǂݍ��݂̃G���[�R�[�h

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState[3] = { nullptr };		//!< �p�C�v���C���X�e�[�g
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;		//!< ���[�g�V�O�l�`��
	};
}

#endif//__MugenEngine_GraphicPipeline__