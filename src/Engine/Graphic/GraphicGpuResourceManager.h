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
#include <list>

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
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEGraphicGpuResourceManager();

		/**********************************************************************//**
			@brief			������
			@param[in]		device				�f�o�C�X
			@param[in]		numVertexBuffer		���_�o�b�t�@�̐�
			@return			�Ȃ�
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const UINT numVertexBuffer);

		/**********************************************************************//**
			@brief			�`�掞�Ƀf�B�X�N���v�^�q�[�v�����R�}���h���X�g�ɐݒ肷��
			@param[in]		cmdList					�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void SetGpuResource(MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			���_�f�[�^���o�b�t�@�ɏ�������
			@param[in]		index						�C���f�b�N�X
			@param[in]		vertices					���_�f�[�^�̐擪�̃|�C���^
			@param[in]		vertexNum					���_�̐�
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadVertexData(const uint32_t index, VERTEX_DATA* vertices, const size_t vertexNum);

		/**********************************************************************//**
			@brief			�萔�o�b�t�@�ɏ�������
			@param[in]		constData					�萔�f�[�^
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadConstantData(CONSTANT_DATA& constData);

		/**********************************************************************//**
			@brief			�V�F�[�_�[���\�[�X�r���[���\�z����
			@param[in]		format				�摜�̃t�H�[�}�b�g
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void CreateSrv(const DXGI_FORMAT format, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�e�N�X�`���̃o�b�t�@���쐬����
			@param[in]		metadata			�摜�̃��^�f�[�^
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void CreateTextureBuffer(const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�A�b�v���[�h�p�̃o�b�t�@���Đݒ肷��
			@param[in]		rowPitch			�摜�̈�s�ӂ�̃f�[�^�T�C�Y
			@param[in]		height				�摜�̍���
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			���ԃo�b�t�@�Ƀf�[�^���A�b�v���[�h����
			@param[in]		srcData			�摜�̐��f�[�^�ւ̃|�C���^
			@param[in]		rowPitch		�摜�̈�s�ӂ�̃f�[�^�T�C�Y
			@param[in]		height			�摜�̍���
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);

		/**********************************************************************//**
			@brief			�e�N�X�`���f�[�^��]������
			@param[in]		metadata					�摜�̃��^�f�[�^
			@param[in]		rowPitch					�摜�f�[�^�̍s�P�ʂ̃T�C�Y
			@param[in]		format						�摜�f�[�^�̃t�H�[�}�b�g
			@param[in]		cmdList						�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadToGpu(DirectX::TexMetadata& metadata, const size_t rowPitch, const DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			CPU��p���ăf�[�^���A�b�v���[�h����
			@param[in]		srcData			�摜�̐��f�[�^�ւ̃|�C���^
			@param[in]		rowPitch		�摜�̈�s�ӂ�̃f�[�^�T�C�Y
			@param[in]		height			�摜�̍���
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadByCpu(uint8_t* srcData, size_t rowPitch, size_t height);

		/**********************************************************************//**
			@brief			���_�o�b�t�@�r���[���擾
			@param[in]		index			�C���f�b�N�X
			@return			�Ȃ�
		*//***********************************************************************/
		D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView(const uint32_t index)
		{
			return m_vertexBufferView[index];
		}

		/**********************************************************************//**
			@brief			�e�N�X�`���q�[�v���擾����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		ID3D12DescriptorHeap* GetTextureHeap()
		{
			return m_basicDescHeap.Get();
		}

		/**********************************************************************//**
			@brief			���_�o�b�t�@���쐬����
			@param[in]		vertexNum					���_�̐�(����3D�`��ɑΉ��������Ȃ炱��͉摜�̖��������K�v)
			@param[in]		device						�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void CreateVertexBuffer(const size_t vertexNum, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�ǉ��̒��_�o�b�t�@���쐬����
			@param[out]		vertexBufferIndex			�ǉ����ꂽ���_�o�b�t�@�̃C���f�b�N�X���i�[����o�b�t�@
			@param[in]		vertexNum					���_�̐�(����3D�`��ɑΉ��������Ȃ炱��͉摜�̖��������K�v)
			@param[in]		device						�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		D3D12_VERTEX_BUFFER_VIEW CreateAdditionalVertexBuffer(int& vertexBufferIndex, const size_t vertexNum, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�ǉ��̒��_�f�[�^���o�b�t�@�ɏ�������
			@param[in]		index						�C���f�b�N�X
			@param[in]		vertices					���_�f�[�^�̐擪�̃|�C���^
			@param[in]		vertexNum					���_�̐�
			@return			�Ȃ�
		*//***********************************************************************/
		void UploadAdditionalVertexData(const uint32_t index, VERTEX_DATA* vertices, const size_t vertexNum);

		/**********************************************************************//**
			@brief			�ǉ��̒��_�o�b�t�@�����Z�b�g����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void ResetAdditionalVertexBuffer() {
			m_currerntAdditionalVertexBufferViewIndex = 0;
		}

	private:
		/**********************************************************************//**
			@brief			�萔�o�b�t�@������������
			@param[in]		device			�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief	�A���C�����g�ɑ�����
			@param size			���̃T�C�Y
			@param alignment		�A���C�����g�T�C�Y
			@return				�A���C�����g�𑵂����T�C�Y
		*//***********************************************************************/
		size_t _GetAlignmentedSize(size_t size, size_t alignment);

		/**********************************************************************//**
			@brief			�w�肵���C���f�b�N�X�ɒ萔�o�b�t�@�r���[���\�z����
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		void _CreateCbv(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�e�N�X�`���f�[�^��]�����钼�O�Ƀo���A��ݒ肷��
			@param[in]		cmdList						�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void _SetBarrierBeforeUploadTexture(const MEGraphicCommandList& cmdList);

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< �f�B�X�N���v�^�q�[�v
		uint32_t m_descriptorHeapIncrementSize;										//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;						//!< �e�N�X�`���̃o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;					//!< �萔�o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< �A�b�v���[�h�p�̒��ԃo�b�t�@
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_vertexBuffer;			//!< ���_�o�b�t�@
		std::vector<D3D12_VERTEX_BUFFER_VIEW> m_vertexBufferView;					//!< ���_�o�b�t�@�r���[
		UINT m_numVertexBuffer;														//!< ���_�o�b�t�@�̐�
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_additionalVertexBuffer;	//!< �ǉ��̒��_�o�b�t�@
		UINT m_numAdditionalVertexBuffer;											//!< �ǉ��̒��_�o�b�t�@�̐�
		UINT m_currerntAdditionalVertexBufferViewIndex;								//!< ���Ɋ��蓖�Ă�ǉ����_�o�b�t�@�r���[
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__