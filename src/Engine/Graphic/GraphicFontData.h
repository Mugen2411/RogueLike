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
		@class		MEFontData
		@brief		�ǂݍ��񂾃t�H���g�ŉ�ʏ�ɕ�����`����s���N���X
	*//***********************************************************************/
	class MEFontData
	{
	public:
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEFontData();

		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param[in]		fontName			�e�N�X�`���𐶐�����t�H���g�̖��O
			@param[in]		fontSize			�t�H���g�T�C�Y
			@return			�Ȃ�
		*//***********************************************************************/
		MEFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		/**********************************************************************//**
			@brief			�R�s�[������Z�q
			@param[in]		rhs					�E��
			@return			���g�̎Q��
		*//***********************************************************************/
		MEFontData & operator= (const MEFontData & rhs);

		/**********************************************************************//**
			@brief			������̕`��
			@param[in]		x					�����X���W
			@param[in]		y					�����Y���W
			@param[in]		color				�����F
			@param[in]		text				�`�悵����������
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawString(const int x, const int y, const float color[4], float priority, const std::wstring text);

		/**********************************************************************//**
			@brief			������̕`��
			@param[in]		x					�����X���W
			@param[in]		y					�����Y���W
			@param[in]		color				�����F
			@param[in]		text				�`�悵����������
			@param[in]		...					����������ɑΉ�����ϐ�����
			@return			�Ȃ�
		*//***********************************************************************/
		void DrawFormatString(const int x, const int y, const float color[4], float priority, const std::wstring text, ...);

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