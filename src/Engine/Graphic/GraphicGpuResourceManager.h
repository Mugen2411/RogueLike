//! @file GraphicGpuResourceManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicGpuResourceManager__
#define __MugenEngine_GraphicGpuResourceManager__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicLoadedImage.h"
#include "GraphicStruct.h"

#include <d3d12.h>
#include <DirectXMath.h>
#include <DirectXTex.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicGpuResourceManager
		@brief		GPU�������Ǘ�����N���X
	*//***********************************************************************/
	class MEGraphicGpuResourceManager
	{
	public:
		//! �R���X�g���N�^
		MEGraphicGpuResourceManager();
		//! ������
		void Initialize(const MEGraphicDevice& device);
		//! �摜��ǂݍ���
		MEGraphicLoadedImage LoadGraph(const std::wstring& filepath, const MEGraphicDevice& device,
			MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! �摜�𕪊����ēǂݍ���
		MEGraphicLoadedImage LoadDivGraph(const std::wstring& filepath, size_t xDivideNum, size_t yDivideNum,
			const MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! GPU���\�[�X���R�}���h���X�g�ɐݒ肷��
		void SetGpuResource(const uint32_t index, MEGraphicCommandList& cmdList);
		//! ���_�f�[�^���o�b�t�@�ɏ�������
		void UploadVertexData(VERTEX_DATA* vertices, size_t vertexNum);
		//! �萔�o�b�t�@�ɏ�������
		void UploadConstantData(const uint32_t index, CONSTANT_DATA& constData);
		//! �`��ΏۂƂ��ăZ�b�g����
		void SetRenderCommand(MEGraphicCommandList& cmdList);
	private:
		//! �萔�o�b�t�@���m�ۂ���
		void _InitalizeConstantBuffer(uint32_t index, const MEGraphicDevice& device);
		//! �A���C�����g�T�C�Y���擾
		size_t _GetAlignmentedSize(size_t size, size_t alignment);
		//! �V�F�[�_�[���\�[�X�r���[�ƃR���X�^���g�o�b�t�@�r���[�𐶐����Ă��ǂ��C���f�b�N�X��Ԃ�
		uint32_t _GetShaderResourceIndex();
		//! �w�肵���C���f�b�N�X�Ƀt�H�[�}�b�g���Q�l��SRV���\�z����
		void _CreateSrv(uint32_t index, const DXGI_FORMAT format,
			const MEGraphicDevice& device);
		//! �w�肵���C���f�b�N�X��CBV���\�z����
		void _CreateCbv(uint32_t index, const MEGraphicDevice& device);
		//! �e�N�X�`���̃o�b�t�@���쐬����
		void _CreateTextureBuffer(const uint32_t index,
			const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);
		//! �A�b�v���[�h�p�̃o�b�t�@���Đݒ肷��
		void _ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);
		//! �A�b�v���[�h�p�̃o�b�t�@�Ƀf�[�^�𗬂�����
		void _UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);
		//! GPU�Ƀe�N�X�`���f�[�^���A�b�v���[�h����
		void _UploadToGpu(uint32_t index, DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);
		//! �e�N�X�`���A�b�v���[�h�O�̃o���A�ݒ�
		void _SetBarrierBeforeUploadTexture(uint32_t index, const MEGraphicCommandList& cmdList);
		//! ���_�o�b�t�@�̍쐬
		void _CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device);

		uint32_t m_currentIndex = 0;												//!< ���݊��蓖�Ă��Ă���摜����
		uint32_t m_maxResourceView = 1024;											//!< ���蓖�Ă���摜�����̍ő�l
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< �f�B�X�N���v�^�q�[�v
		uint32_t m_descriptorHeapIncrementSize;										//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_textureBuffers;		//!< �e�N�X�`���̃o�b�t�@
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;		//!< �萔�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< �A�b�v���[�h�p�̒��ԃo�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;			//!< ���_�o�b�t�@
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;								//!< ���_�o�b�t�@�r���[
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__