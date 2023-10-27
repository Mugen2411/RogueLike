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
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEImage();

		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param[in]		filepath			�摜�̃t�@�C���p�X
			@param[in]		device				�f�o�C�X
			@param[in]		xDivideNum			�������̕�����
			@param[in]		yDivideNum			�c�����̕�����
			@param[in]		cmdList				�R�}���h���X�g
			@param[in]		pipeline			�p�C�v���C��
			@param[in]		renderTarget		�����_�[�^�[�Q�b�g
			@return			�Ȃ�
		*//***********************************************************************/
		MEImage(const std::wstring& filepath, MEGraphicDevice& device, size_t xDivideNum, size_t yDivideNum,
			MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		/**********************************************************************//**
			@enum		BLEND_TYPE
			@brief		�摜�̍�������
		*//***********************************************************************/
		enum BLEND_TYPE
		{
			ALPHA = 0, ADD, SUB
		};

		/**********************************************************************//**
			@brief			�w�肵�����W�ɕ`��
			@param[in]		x					�`�悷�钆�S��X���W
			@param[in]		y					�`�悷�钆�S��Y���W
			@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawGraph(const int x, const int y, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			���W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
			@param[in]		x					�`�悷�钆�S��X���W
			@param[in]		y					�`�悷�钆�S��Y���W
			@param[in]		scale				�g�嗦
			@param[in]		angle				��]�p�x(���W�A��)
			@param[in]		priority			�`��D��x
			@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawRotaGraph(const int x, const int y, const float scale, const float angle, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			2�{���Z�Ŏw�肵�����W�ɕ`��
			@param[in]		x					�`�悷�钆�S��X���W
			@param[in]		y					�`�悷�钆�S��Y���W
			@param[in]		priority			�`��D��x
			@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawGraph2X(const int x, const int y, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			2�{���Z�ō��W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
			@param[in]		x					�`�悷�钆�S��X���W
			@param[in]		y					�`�悷�钆�S��Y���W
			@param[in]		scale				�g�嗦
			@param[in]		angle				��]�p�x(���W�A��)
			@param[in]		priority			�`��D��x
			@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawRotaGraph2X(const int x, const int y, const float scale, const float angle,
			const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			���R��4���_���w�肵�ĕ`��
			@param[in]		x0					X���W
			@param[in]		y0					Y���W
			@param[in]		x1					X���W
			@param[in]		y1					Y���W
			@param[in]		x2					X���W
			@param[in]		y2					Y���W
			@param[in]		x3					X���W
			@param[in]		y3					Y���W
			@param[in]		priority			�`��D��x
			@param[in]		index				�C���f�b�N�X
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawModiGraph(const int x0, const int y0, const int x1, const int y1,
			const int x2, const int y2, const int x3, const int y3, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			���R��4���_���w�肵�ĕ`��
			@param[in]		x0					X���W
			@param[in]		y0					Y���W
			@param[in]		x1					X���W
			@param[in]		y1					Y���W
			@param[in]		x2					X���W
			@param[in]		y2					Y���W
			@param[in]		x3					X���W
			@param[in]		y3					Y���W
			@param[in]		priority			�`��D��x
			@param[in]		index				�C���f�b�N�X
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawModiGraph2X(const int x0, const int y0, const int x1, const int y1,
			const int x2, const int y2, const int x3, const int y3, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			�摜�`�掞�̋P�x��ݒ�
			@param[in]		R					��
			@param[in]		G					��
			@param[in]		B					��
			@param[in]		A					�s�����x
			@return			�Ȃ�
		*//***********************************************************************/
		void SetBrightness(const float R, const float G, const float B, const float A);

		/**********************************************************************//**
			@brief			�摜�`�掞�̃u�����h�^�C�v��ݒ�
			@param[in]		blendType					�u�����h�^�C�v
			@return			�Ȃ�
		*//***********************************************************************/
		void SetBlendType(const BLEND_TYPE blendType);

		/**********************************************************************//**
			@brief			�ǉ��̒��_�o�b�t�@�����Z�b�g
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void ResetAdditionalVertexBuffer();
		
	private:
		size_t m_width;												//!< �摜�̉���
		size_t m_height;											//!< �摜�̍���
		size_t m_xDivideNum;										//!< �������̕�����
		size_t m_yDivideNum;										//!< �c�����̕�����
		VERTEX_DATA m_vertices[4];									//!< �|���S���Ƃ��ĕ\�����邽�߂̒��_
		DirectX::XMFLOAT4 m_brightness;								//!< �P�x�x�N�g��
		BLEND_TYPE m_blendType;										//!< �u�����h�^�C�v
		MEGraphicDevice* m_pDevice;									//!< �f�o�C�X
		MEGraphicCommandList* m_pCmdList;							//!< �R�}���h���X�g
		MEGraphicGpuResourceManager m_resourceManager;				//!< ���\�[�X�}�l�[�W���[
		MEGraphicPipeline* m_pPipeline;								//!< �p�C�v���C��
		MEGraphicRenderTarget* m_pRenderTarget;						//!< �����_�[�^�[�Q�b�g
	};
}

#endif//__MugenEngine_GraphicLoadedImage__