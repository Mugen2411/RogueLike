//! @file GraphicLoadedImage.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicLoadedImage__
#define __MugenEngine_GraphicLoadedImage__

#include <cstdint>
#include <DirectXMath.h>
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicStruct.h"

namespace mugen_engine
{
	class MEGraphicGpuResourceManager;
	/**********************************************************************//**
		@class		MEGraphicLoadedImage
		@brief		�ǂݍ��ݍς݉摜�������N���X
	*//***********************************************************************/
	class MEGraphicLoadedImage
	{
	public:
		//! �R���X�g���N�^
		MEGraphicLoadedImage();
		//! �R���X�g���N�^
		MEGraphicLoadedImage(uint32_t index, size_t width, size_t height, 
			MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager,
			MEGraphicPipeline* pipeline, MEGraphicRenderTarget* renderTarget);
		//! �w�肵�����W�ɕ`��
		void DrawGraph(int x, int y);
	private:
		uint32_t m_index;											//!< �ǂݍ��݉摜�����Ԗڂ�
		size_t m_width;												//!< �摜�̉���
		size_t m_height;											//!< �摜�̍���
		size_t m_xDivideNum;										//!< �������̕�����
		size_t m_yDivideNum;										//!< �c�����̕�����
		VERTEX_DATA m_vertices[4];									//!< �|���S���Ƃ��ĕ\�����邽�߂̒��_
		DirectX::XMMATRIX m_matrix;									//!< �ό`�s��
		MEGraphicCommandList* m_cmdList;							//!< �R�}���h���X�g
		MEGraphicGpuResourceManager* m_resourceManager;				//!< ���\�[�X�}�l�[�W���[
		MEGraphicPipeline* m_pipeline;								//!< �p�C�v���C��
		MEGraphicRenderTarget* m_renderTarget;						//!< �����_�[�^�[�Q�b�g
	};
}

#endif//__MugenEngine_GraphicLoadedImage__