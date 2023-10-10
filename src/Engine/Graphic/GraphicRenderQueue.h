//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderQueue__
#define __MugenEngine_GraphicRenderQueue__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicStruct.h"
#include <list>
#include <DirectXTex.h>

namespace mugen_engine
{
	class MEGraphicRenderQueue
	{
	public:
		//! ������
		static void Initialize(MEGraphicDevice& device);
		//! �`���\�񂷂�
		static void ReserveRender(D3D12_VERTEX_BUFFER_VIEW* vbView, CONSTANT_DATA constData,
			ID3D12DescriptorHeap* textureHeap, int blendType, MEGraphicCommandList* cmdList, MEGraphicPipeline* pipeline,
			MEGraphicRenderTarget* renderTarget);
		//! �\�񂵂��`����s��
		static void RenderAll(MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
	private:
		/**********************************************************************//**
			@struct		RENDER_DATA
			@brief		�l�p�`�̃|���S�����ꖇ�`�悷��P��
		*//***********************************************************************/
		struct RENDER_DATA
		{
			D3D12_VERTEX_BUFFER_VIEW* vertexBufferView;			//!< ���_�o�b�t�@�r���[
			ID3D12DescriptorHeap* textureHeap;					//!< �e�N�X�`���̃f�B�X�N���v�^�q�[�v
			int blendType;										//!< �u�����h�^�C�v
		};

		//! �w�肵���C���f�b�N�X��CBV���\�z����
		static void _CreateCbv(uint32_t index, const MEGraphicDevice& device);
		//! �萔�o�b�t�@���m�ۂ���
		static void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_constantDescHeap;		//!< �萔�p�̃f�B�X�N���v�^�q�[�v
		static std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;//!< �萔�o�b�t�@
		static int m_currentReserved;												//!< ���ݕ`��\��L���[�ɓ����Ă��鐔
		static int m_maxReserve;													//!< �`��\��\�ȍő吔
		static std::vector<RENDER_DATA> m_reserveList;								//!< �`��\��L���[
		static uint32_t m_descriptorHeapIncrementSize;								//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		static MEGraphicDevice* m_pDevice;											//!< �f�o�C�X
		static std::vector<CONSTANT_DATA*> m_pMapMatrix;							//!< �}�b�v���ꂽ�萔�o�b�t�@
	};
}

#endif//__MugenEngine_GraphicRenderQueue__