//! @file GraphicFontData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicFontData.h"

namespace mugen_engine
{
	MEGraphicFontData::MEGraphicFontData()
	{}
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		fontName			テクスチャを生成するフォントの名前
		@param[in]		fontSize			フォントサイズ
		@return			なし
	*//***********************************************************************/
	MEGraphicFontData::MEGraphicFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
		MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget): 
		m_pDevice(&device), m_pCmdList(&cmdList), m_pPipeline(&pipeline), m_pRenderTarget(&renderTarget)
	{
		LOGFONT lf =
		{
			fontSize, 0, 0, 0, 1000, 0, 0, 0,
			SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
			L'\0'
		};
		for(size_t i = 0; i < fontName.size(); ++i)
		{
			lf.lfFaceName[i] = fontName[i];
		}
		HFONT hFont = CreateFontIndirectW(&lf);

		// 現在のウィンドウに適用
		// デバイスにフォントを持たせないとGetGlyphOutlineW関数はエラーとなる
		m_hdc = GetDC(NULL);
		m_oldFont = (HFONT)SelectObject(m_hdc, hFont);
	}

	/**********************************************************************//**
		@brief			コピー代入演算子
		@param[in]		rhs					右辺
		@return			自身の参照
	*//***********************************************************************/
	MEGraphicFontData& MEGraphicFontData::operator=(const MEGraphicFontData& rhs)
	{
		this->m_hdc = rhs.m_hdc;
		this->m_oldFont = rhs.m_oldFont;
		this->m_loadedCharacters.clear();

		this->m_pDevice = rhs.m_pDevice;
		this->m_pCmdList = rhs.m_pCmdList;
		this->m_pPipeline = rhs.m_pPipeline;
		this->m_pRenderTarget = rhs.m_pRenderTarget;
		
		return *this;
	}

	void MEGraphicFontData::DrawString(int x, int y, float color[4], std::wstring text)
	{
		size_t xOffset = 0;
		size_t yOffset = 0;
		for(size_t currentOffset = 0; currentOffset < text.size(); ++currentOffset)
		{
			auto character = m_loadedCharacters.find(text[currentOffset]);
			if(character == m_loadedCharacters.end())
			{
				m_loadedCharacters[text[currentOffset]] = MEGraphicCharacterUnit(text[currentOffset], m_oldFont, m_hdc,
					*m_pDevice, *m_pCmdList, *m_pPipeline, *m_pRenderTarget);
			}
			auto& cur = m_loadedCharacters[text[currentOffset]];
			if(text[currentOffset] != L'\n')
			{
				cur.DrawCharacter(x + static_cast<int>(xOffset), y + static_cast<int>(yOffset), color);
				xOffset += m_loadedCharacters[text[currentOffset]].m_width;
			}
			else
			{
				yOffset += cur.m_height;
				xOffset = 0;
			}
		}
	}
}