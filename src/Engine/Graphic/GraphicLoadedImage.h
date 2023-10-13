//! @file GraphicLoadedImage.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicLoadedImage__
#define __MugenEngine_GraphicLoadedImage__

#include <cstdint>
#include <DirectXMath.h>
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicGpuResourceManager.h"
#include "GraphicStruct.h"

namespace mugen_engine
{
	class MEGraphicGpuResourceManager;
	/**********************************************************************//**
		@class		MEImage
		@brief		�ǂݍ��ݍς݉摜�������N���X
	*//***********************************************************************/
	class MEImage
	{
	public:
		//! �R���X�g���N�^
		MEImage();
		//! �R���X�g���N�^
		MEImage(const std::wstring& filepath, MEGraphicDevice& device, size_t xDivideNum, size_t yDivideNum,
			MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		enum BLEND_TYPE
		{
			ALPHA = 0, ADD, SUB
		};

		//! �w�肵�����W�ɕ`��
		void DrawGraph(int x, int y, float priority,int index = 0);
		//! ���W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
		void DrawRotaGraph(int x, int y, float scale, float angle, float priority, int index = 0);
		//! 2�{���Z�Ŏw�肵�����W�ɕ`��
		void DrawGraph2X(int x, int y, float priority, int index = 0);
		//! 2�{���Z�ō��W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
		void DrawRotaGraph2X(int x, int y, float scale, float angle, float priority, int index = 0);
		//! �摜�`�掞�̋P�x��ݒ肷��
		void SetBrightness(const float R, const float G, const float B, const float A);
		//! �摜�`�掞�̃u�����h�^�C�v��ݒ肷��
		void SetBlendType(BLEND_TYPE blendType);
		
	private:
		size_t m_width;												//!< �摜�̉���
		size_t m_height;											//!< �摜�̍���
		size_t m_xDivideNum;										//!< �������̕�����
		size_t m_yDivideNum;										//!< �c�����̕�����
		VERTEX_DATA m_vertices[4];									//!< �|���S���Ƃ��ĕ\�����邽�߂̒��_
		DirectX::XMFLOAT4 m_brightness;								//!< �P�x�x�N�g��
		BLEND_TYPE m_blendType;										//!< �u�����h�^�C�v
		MEGraphicCommandList* m_pCmdList;							//!< �R�}���h���X�g
		MEGraphicGpuResourceManager m_resourceManager;				//!< ���\�[�X�}�l�[�W���[
		MEGraphicPipeline* m_pPipeline;								//!< �p�C�v���C��
		MEGraphicRenderTarget* m_pRenderTarget;						//!< �����_�[�^�[�Q�b�g
	};
}

#endif//__MugenEngine_GraphicLoadedImage__