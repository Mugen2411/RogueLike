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
		@brief		読み込んだフォントで画面上に文字列描画を行うクラス
	*//***********************************************************************/
	class MEGraphicFontData
	{
	public:
		//! コンストラクタ
		MEGraphicFontData();
		//! コンストラクタ
		MEGraphicFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! コピー代入演算子
		MEGraphicFontData & operator= (const MEGraphicFontData & rhs);
		//! 文字列の描画を行う
		void DrawString(const int x, const int y, float color[4], const std::wstring text);
		//! 書式文字列を描画する
		void DrawFormatString(const int x, const int y, float color[4], const std::wstring text, ...);
	private:
		HDC m_hdc;																//!< ハンドル
		HFONT m_oldFont;														//!< 文字テクスチャに渡すフォント本体
		std::unordered_map<wchar_t, MEGraphicCharacterUnit> m_loadedCharacters;	//!< 各文字のテクスチャ

		MEGraphicDevice* m_pDevice;												//!< デバイス
		MEGraphicCommandList* m_pCmdList;											//!< コマンドリスト
		MEGraphicPipeline* m_pPipeline;											//!< パイプライン
		MEGraphicRenderTarget* m_pRenderTarget;									//!< レンダーターゲット
	};
}

#endif//__MugenEngine_GraphicFontData__