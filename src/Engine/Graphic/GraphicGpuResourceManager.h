//! @file GraphicGpuResourceManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicGpuResourceManager__
#define __MugenEngine_GraphicGpuResourceManager__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
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
		//! GPU���\�[�X���R�}���h���X�g�ɐݒ肷��
		void SetGpuResource(MEGraphicCommandList& cmdList);
		//! ���_�f�[�^���o�b�t�@�ɏ�������
		void UploadVertexData(VERTEX_DATA* vertices, size_t vertexNum);
		//! �萔�o�b�t�@�ɏ�������
		void UploadConstantData(CONSTANT_DATA& constData);
		//! �`��ΏۂƂ��ăZ�b�g����
		void SetRenderCommand(MEGraphicCommandList& cmdList);
		//! �w�肵���C���f�b�N�X�Ƀt�H�[�}�b�g���Q�l��SRV���\�z����
		void CreateSrv(const DXGI_FORMAT format,
			const MEGraphicDevice& device);
		//! �e�N�X�`���̃o�b�t�@���쐬����
		void CreateTextureBuffer(const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);
		//! �A�b�v���[�h�p�̃o�b�t�@���Đݒ肷��
		void ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);
		//! �A�b�v���[�h�p�̃o�b�t�@�Ƀf�[�^�𗬂�����
		void UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);
		//! GPU�Ƀe�N�X�`���f�[�^���A�b�v���[�h����
		void UploadToGpu(DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);
		//! CPU�œ]������
		void UploadByCpu(uint8_t* srcData, size_t rowPitch, size_t height);
		//! ���_�o�b�t�@�r���[���擾
		D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView()
		{
			return &m_vertexBufferView;
		}
		//! �e�N�X�`���p�q�[�v���擾
		ID3D12DescriptorHeap* GetTextureHeap()
		{
			return m_basicDescHeap.Get();
		}
	private:
		//! �萔�o�b�t�@���m�ۂ���
		void _InitalizeConstantBuffer(const MEGraphicDevice& device);
		//! �A���C�����g�T�C�Y���擾
		size_t _GetAlignmentedSize(size_t size, size_t alignment);
		//! �w�肵���C���f�b�N�X��CBV���\�z����
		void _CreateCbv(const MEGraphicDevice& device);
		//! �e�N�X�`���A�b�v���[�h�O�̃o���A�ݒ�
		void _SetBarrierBeforeUploadTexture(const MEGraphicCommandList& cmdList);
		//! ���_�o�b�t�@�̍쐬
		void _CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device);

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< �f�B�X�N���v�^�q�[�v
		uint32_t m_descriptorHeapIncrementSize;										//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;						//!< �e�N�X�`���̃o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;					//!< �萔�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< �A�b�v���[�h�p�̒��ԃo�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;			//!< ���_�o�b�t�@
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;								//!< ���_�o�b�t�@�r���[
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__