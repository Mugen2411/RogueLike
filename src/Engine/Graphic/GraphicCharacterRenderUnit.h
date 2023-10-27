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
		@brief		フォントから特定の文字のテクスチャを作り保持するクラス
	*//***********************************************************************/
	class MEGraphicCharacterUnit
	{
	public:
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicCharacterUnit();

		/**********************************************************************//**
			@brief			コンストラクタ
			@param[in]		character			テクスチャに変換する文字
			@param[in]		fontData			フォント
			@param[in]		hdc					デバイスコンテキスト
			@param[in]		device				デバイス
			@param[in]		cmdList				コマンドリスト
			@param[in]		pipeline			パイプライン
			@param[in]		renderTarget		レンダーターゲット
			@return			なし
		*//***********************************************************************/
		MEGraphicCharacterUnit(const wchar_t character, HFONT fontData, HDC hdc,
			MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		/**********************************************************************//**
			@brief			文字を描画
			@param[in]		x					左上のX座標
			@param[in]		y					左上のY座標
			@param[in]		color				文字色
			@return			なし
		*//***********************************************************************/
		void DrawCharacter(const int x, const int y, const float color[4], const float priority);
	private:
		/**********************************************************************//**
		@struct		TexRGBA
		@brief		テクスチャの画素を表現する構造体
	*//***********************************************************************/
		struct TexRGBA
		{
			unsigned char R, G, B, A;			//!< RGBA
		};

		size_t m_width;												//!< 画像の横幅
		size_t m_height;											//!< 画像の高さ
		VERTEX_DATA m_vertices[4];									//!< 板ポリゴンとして表示するための頂点
		MEGraphicCommandList* m_pCmdList;							//!< コマンドリスト
		MEGraphicGpuResourceManager m_resourceManager;				//!< リソースマネージャー
		MEGraphicPipeline* m_pPipeline;								//!< パイプライン
		MEGraphicRenderTarget* m_pRenderTarget;						//!< レンダーターゲット

		friend MEFontData;
	};
}

#endif//__MugenEngine_GraphicCharacterRenderUnit__