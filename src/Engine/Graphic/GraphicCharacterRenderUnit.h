//! @file GraphicCharacterRenderUnit.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCharacterRenderUnit__
#define __MugenEngine_GraphicCharacterRenderUnit__

#include "GraphicGpuResourceManager.h"
#include <d3d12.h>
#include <DirectXTex.h>

namespace mugen_engine
{
	class MEGraphicCommandList;
	class MEGraphicPipeline;
	class MEGraphicRenderTarget;
	class MEFontData;
	/**********************************************************************//**
		@class		MEGraphicCharacterUnit
		@brief		�t�H���g�������̕����̃e�N�X�`�������ێ�����N���X
	*//***********************************************************************/
	class MEGraphicCharacterUnit
	{
	public:
		//! �R���X�g���N�^
		MEGraphicCharacterUnit();
		//! �R���X�g���N�^
		MEGraphicCharacterUnit(const wchar_t character, HFONT fontData, HDC hdc,
			MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! �w�肵���ʒu�ɕ`��
		void DrawCharacter(const int x, const int y, float color[4], float priority);
	private:
		/**********************************************************************//**
		@struct		TexRGBA
		@brief		�e�N�X�`���̉�f��\������\����
	*//***********************************************************************/
		struct TexRGBA
		{
			unsigned char R, G, B, A;			//!< RGBA
		};

		size_t m_width;												//!< �摜�̉���
		size_t m_height;											//!< �摜�̍���
		VERTEX_DATA m_vertices[4];									//!< �|���S���Ƃ��ĕ\�����邽�߂̒��_
		MEGraphicCommandList* m_pCmdList;							//!< �R�}���h���X�g
		MEGraphicGpuResourceManager m_resourceManager;				//!< ���\�[�X�}�l�[�W���[
		MEGraphicPipeline* m_pPipeline;								//!< �p�C�v���C��
		MEGraphicRenderTarget* m_pRenderTarget;						//!< �����_�[�^�[�Q�b�g

		friend MEFontData;
	};
}

#endif//__MugenEngine_GraphicCharacterRenderUnit__