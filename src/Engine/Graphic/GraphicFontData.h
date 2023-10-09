//! @file GraphicFontData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicFontData__
#define __MugenEngine_GraphicFontData__

#include "GraphicCharacterRenderUnit.h"

#include <unordered_map>
#include <wingdi.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicFontData
		@brief		�ǂݍ��񂾃t�H���g�ŉ�ʏ�ɕ�����`����s���N���X
	*//***********************************************************************/
	class MEGraphicFontData
	{
	public:
		//! �R���X�g���N�^
		MEGraphicFontData();
		//! �R���X�g���N�^
		MEGraphicFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! �R�s�[������Z�q
		MEGraphicFontData & operator= (const MEGraphicFontData & rhs);
		//! ������̕`����s��
		void DrawString(const int x, const int y, float color[4], const std::wstring text);
		//! �����������`�悷��
		void DrawFormatString(const int x, const int y, float color[4], const std::wstring text, ...);
	private:
		HDC m_hdc;																//!< �n���h��
		HFONT m_oldFont;														//!< �����e�N�X�`���ɓn���t�H���g�{��
		std::unordered_map<wchar_t, MEGraphicCharacterUnit> m_loadedCharacters;	//!< �e�����̃e�N�X�`��

		MEGraphicDevice* m_pDevice;												//!< �f�o�C�X
		MEGraphicCommandList* m_pCmdList;											//!< �R�}���h���X�g
		MEGraphicPipeline* m_pPipeline;											//!< �p�C�v���C��
		MEGraphicRenderTarget* m_pRenderTarget;									//!< �����_�[�^�[�Q�b�g
	};
}

#endif//__MugenEngine_GraphicFontData__