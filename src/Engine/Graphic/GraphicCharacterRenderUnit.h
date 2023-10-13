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
		//! コンストラクタ
		MEGraphicCharacterUnit();
		//! コンストラクタ
		MEGraphicCharacterUnit(const wchar_t character, HFONT fontData, HDC hdc,
			MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! 指定した位置に描画
		void DrawCharacter(const int x, const int y, float color[4], float priority);
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