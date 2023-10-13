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
		@brief		読み込み済み画像を扱うクラス
	*//***********************************************************************/
	class MEImage
	{
	public:
		//! コンストラクタ
		MEImage();
		//! コンストラクタ
		MEImage(const std::wstring& filepath, MEGraphicDevice& device, size_t xDivideNum, size_t yDivideNum,
			MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		enum BLEND_TYPE
		{
			ALPHA = 0, ADD, SUB
		};

		//! 指定した座標に描画
		void DrawGraph(int x, int y, float priority,int index = 0);
		//! 座標と拡大率と回転角度を指定して描画
		void DrawRotaGraph(int x, int y, float scale, float angle, float priority, int index = 0);
		//! 2倍換算で指定した座標に描画
		void DrawGraph2X(int x, int y, float priority, int index = 0);
		//! 2倍換算で座標と拡大率と回転角度を指定して描画
		void DrawRotaGraph2X(int x, int y, float scale, float angle, float priority, int index = 0);
		//! 画像描画時の輝度を設定する
		void SetBrightness(const float R, const float G, const float B, const float A);
		//! 画像描画時のブレンドタイプを設定する
		void SetBlendType(BLEND_TYPE blendType);
		
	private:
		size_t m_width;												//!< 画像の横幅
		size_t m_height;											//!< 画像の高さ
		size_t m_xDivideNum;										//!< 横方向の分割数
		size_t m_yDivideNum;										//!< 縦方向の分割数
		VERTEX_DATA m_vertices[4];									//!< 板ポリゴンとして表示するための頂点
		DirectX::XMFLOAT4 m_brightness;								//!< 輝度ベクトル
		BLEND_TYPE m_blendType;										//!< ブレンドタイプ
		MEGraphicCommandList* m_pCmdList;							//!< コマンドリスト
		MEGraphicGpuResourceManager m_resourceManager;				//!< リソースマネージャー
		MEGraphicPipeline* m_pPipeline;								//!< パイプライン
		MEGraphicRenderTarget* m_pRenderTarget;						//!< レンダーターゲット
	};
}

#endif//__MugenEngine_GraphicLoadedImage__