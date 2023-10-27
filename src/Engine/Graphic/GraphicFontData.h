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
		@brief		読み込んだフォントで画面上に文字列描画を行うクラス
	*//***********************************************************************/
	class MEFontData
	{
	public:
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEFontData();

		/**********************************************************************//**
			@brief			コンストラクタ
			@param[in]		fontName			テクスチャを生成するフォントの名前
			@param[in]		fontSize			フォントサイズ
			@return			なし
		*//***********************************************************************/
		MEFontData(std::wstring fontName, int fontSize, MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		/**********************************************************************//**
			@brief			コピー代入演算子
			@param[in]		rhs					右辺
			@return			自身の参照
		*//***********************************************************************/
		MEFontData & operator= (const MEFontData & rhs);

		/**********************************************************************//**
			@brief			文字列の描画
			@param[in]		x					左上のX座標
			@param[in]		y					左上のY座標
			@param[in]		color				文字色
			@param[in]		text				描画したい文字列
			@return			なし
		*//***********************************************************************/
		void DrawString(const int x, const int y, const float color[4], float priority, const std::wstring text);

		/**********************************************************************//**
			@brief			文字列の描画
			@param[in]		x					左上のX座標
			@param[in]		y					左上のY座標
			@param[in]		color				文字色
			@param[in]		text				描画したい文字列
			@param[in]		...					書式文字列に対応する変数たち
			@return			なし
		*//***********************************************************************/
		void DrawFormatString(const int x, const int y, const float color[4], float priority, const std::wstring text, ...);

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