//! @file GraphicFontData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicFontData.h"
#include <memory>

namespace mugen_engine
{
	MEFontData::MEFontData()
	{}
	
	MEFontData::MEFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
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
		assert(hFont != NULL);

		// 現在のウィンドウに適用
		// デバイスにフォントを持たせないとGetGlyphOutlineW関数はエラーとなる
		m_hdc = GetDC(NULL);
		assert(m_hdc != NULL);
		m_oldFont = (HFONT)SelectObject(m_hdc, hFont);
	}

	MEFontData& MEFontData::operator=(const MEFontData& rhs)
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

	void MEFontData::DrawString(const int x, const int y, const float color[4], const float priority, const std::wstring text)
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
			if(text[currentOffset] == L'\n')
			{
				yOffset += cur.m_height;
				xOffset = 0;
			}
			else if (text[currentOffset] == L' ')
			{
				xOffset += m_loadedCharacters[text[currentOffset]].m_width;
			}
			else
			{
				cur.DrawCharacter(x + static_cast<int>(xOffset), y + static_cast<int>(yOffset), color, priority);
				xOffset += m_loadedCharacters[text[currentOffset]].m_width;
			}
		}
	}

	void MEFontData::DrawFormatString(const int x, const int y, const float color[4], const float priority, const std::wstring text, ...)
	{
		va_list args;
		va_start(args, text);
		const int len = _vscwprintf_p(text.c_str(), args);
		wchar_t* buf = new wchar_t[len + 1];
		vswprintf_s(buf, len + 1, text.c_str(), args);
		DrawString(x, y, color, priority, buf);
		delete[] buf;
		va_end(args);
	}
}