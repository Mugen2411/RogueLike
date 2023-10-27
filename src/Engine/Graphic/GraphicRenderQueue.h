//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderQueue__
#define __MugenEngine_GraphicRenderQueue__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicGpuResourceManager.h"
#include "GraphicStruct.h"
#include <deque>
#include <DirectXTex.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicRenderQueue
		@brief		�`��҂��̉摜��~���ď�������N���X
	*//***********************************************************************/
	class MEGraphicRenderQueue
	{
	public:
		/**********************************************************************//**
			@brief			������
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		static void Initialize(MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�`���\�񂷂�
			@param[in]		vbView				���_�o�b�t�@�r���[
			@param[in]		constData			�萔�o�b�t�@�̃f�[�^
			@param[in]		textureHeap			�e�N�X�`���̃f�B�X�N���v�^�q�[�v
			@param[in]		blendType			�u�����h�^�C�v
			@param[in]		priority			�`��D��x
			@param[in]		cmdList				�R�}���h���X�g
			@param[in]		pipeline			�p�C�v���C��
			@param[in]		renderTarget		�����_�[�^�[�Q�b�g
			@return			�Ȃ�
		*//***********************************************************************/
		static void ReserveRender(const D3D12_VERTEX_BUFFER_VIEW vbView, const CONSTANT_DATA constData,
			MEGraphicGpuResourceManager* textureHeap, const int blendType, const float priority,
			MEGraphicCommandList* cmdList, MEGraphicPipeline* pipeline,
			MEGraphicRenderTarget* renderTarget);
		
		/**********************************************************************//**
			@brief			�\�񂳂ꂽ�`���S�����΂���
			@param[in]		cmdList				�R�}���h���X�g
			@param[in]		pipeline			�p�C�v���C��
			@param[in]		renderTarget		�����_�[�^�[�Q�b�g
			@return			�Ȃ�
		*//***********************************************************************/
		static void RenderAll(MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

	private:
		/**********************************************************************//**
			@struct		RENDER_DATA
			@brief		�l�p�`�̃|���S�����ꖇ�`�悷��P��
		*//***********************************************************************/
		struct RENDER_DATA
		{
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;			//!< ���_�o�b�t�@�r���[
			MEGraphicGpuResourceManager* textureHeap;			//!< �e�N�X�`���̃f�B�X�N���v�^�q�[�v
			int blendType;										//!< �u�����h�^�C�v
			CONSTANT_DATA constData;							//!< �萔�f�[�^
			float priority;										//!< �`��D��x
			size_t order;										//!< �\�񂳂ꂽ����
		};

		/**********************************************************************//**
			@brief			�w�肵���C���f�b�N�X�ɒ萔�o�b�t�@�r���[���\�z����
			@param[in]		index				�������Ɋ��蓖�Ă�ꂽ�C���f�b�N�X
			@param[in]		device				�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		static void _CreateCbv(const uint32_t index, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�萔�o�b�t�@������������
			@param[in]		device			�f�o�C�X
			@return			�Ȃ�
		*//***********************************************************************/
		static void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_constantDescHeap;			//!< �萔�p�̃f�B�X�N���v�^�q�[�v
		static std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;	//!< �萔�o�b�t�@
		static int m_maxReserve;														//!< �`��\��\�ȍő吔
		static std::deque<RENDER_DATA> m_reserveList;									//!< �`��\��L���[
		static std::vector<const RENDER_DATA*> m_reservePointerList;					//!< �\�[�g�Ɏg���|�C���^�̔z��
		static uint32_t m_descriptorHeapIncrementSize;									//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		static MEGraphicDevice* m_pDevice;												//!< �f�o�C�X
		static std::vector<CONSTANT_DATA*> m_pMapMatrix;								//!< �}�b�v���ꂽ�萔�o�b�t�@
	};
}

#endif//__MugenEngine_GraphicRenderQueue__