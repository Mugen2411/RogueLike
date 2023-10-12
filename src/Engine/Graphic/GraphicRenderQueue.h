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
	class MEGraphicRenderQueue
	{
	public:
		//! ������
		static void Initialize(MEGraphicDevice& device);
		//! �`���\�񂷂�
		static void ReserveRender(D3D12_VERTEX_BUFFER_VIEW* vbView, CONSTANT_DATA constData,
			MEGraphicGpuResourceManager* textureHeap, int blendType, float priority, MEGraphicCommandList* cmdList, MEGraphicPipeline* pipeline,
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
			MEGraphicGpuResourceManager* textureHeap;			//!< �e�N�X�`���̃f�B�X�N���v�^�q�[�v
			int blendType;										//!< �u�����h�^�C�v
			CONSTANT_DATA constData;							//!< �萔�f�[�^
			float priority;										//!< �`��D��x
			size_t order;											//!< �\�񂳂ꂽ����
		};

		//! �w�肵���C���f�b�N�X��CBV���\�z����
		static void _CreateCbv(uint32_t index, const MEGraphicDevice& device);
		//! �萔�o�b�t�@���m�ۂ���
		static void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_constantDescHeap;		//!< �萔�p�̃f�B�X�N���v�^�q�[�v
		static std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;//!< �萔�o�b�t�@
		static int m_maxReserve;													//!< �`��\��\�ȍő吔
		static std::deque<RENDER_DATA> m_reserveList;								//!< �`��\��L���[
		static std::vector<const RENDER_DATA*> m_reservePointerList;						//!< �\�[�g�Ɏg���|�C���^�̔z��
		static uint32_t m_descriptorHeapIncrementSize;								//!< SRV��CBV�ɂ�����f�B�X�N���v�^�q�[�v��̃T�C�Y
		static MEGraphicDevice* m_pDevice;											//!< �f�o�C�X
		static std::vector<CONSTANT_DATA*> m_pMapMatrix;							//!< �}�b�v���ꂽ�萔�o�b�t�@
	};
}

#endif//__MugenEngine_GraphicRenderQueue__