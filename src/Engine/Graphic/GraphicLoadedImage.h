//! @file GraphicLoadedImage.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicLoadedImage__
#define __MugenEngine_GraphicLoadedImage__

#include <cstdint>
#include <DirectXMath.h>
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicStruct.h"

namespace mugen_engine
{
	class MEGraphicGpuResourceManager;
	/**********************************************************************//**
		@class		MEGraphicLoadedImage
		@brief		読み込み済み画像を扱うクラス
	*//***********************************************************************/
	class MEGraphicLoadedImage
	{
	public:
		//! コンストラクタ
		MEGraphicLoadedImage();
		//! コンストラクタ
		MEGraphicLoadedImage(uint32_t index, size_t width, size_t height, 
			MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager,
			MEGraphicPipeline* pipeline, MEGraphicRenderTarget* renderTarget);
		//! コンストラクタ
		MEGraphicLoadedImage(uint32_t index, size_t width, size_t height, size_t xDivideNum, size_t yDivideNum,
			MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager,
			MEGraphicPipeline* pipeline, MEGraphicRenderTarget* renderTarget);
		//! 指定した座標に描画
		void DrawGraph(int x, int y, int index = 0);
		//! 座標と拡大率と回転角度を指定して描画
		void DrawRotaGraph(int x, int y, float scale, float angle, int index = 0);
		//! 画像描画時の輝度を設定する
		void SetBrightness(const float R, const float G, const float B, const float A);
	private:
		uint32_t m_index;											//!< 読み込み画像が何番目か
		size_t m_width;												//!< 画像の横幅
		size_t m_height;											//!< 画像の高さ
		size_t m_xDivideNum;										//!< 横方向の分割数
		size_t m_yDivideNum;										//!< 縦方向の分割数
		VERTEX_DATA m_vertices[4];									//!< 板ポリゴンとして表示するための頂点
		DirectX::XMMATRIX m_matrix;									//!< 変形行列
		DirectX::XMFLOAT4 m_brightness;								//!< 輝度ベクトル
		MEGraphicCommandList* m_cmdList;							//!< コマンドリスト
		MEGraphicGpuResourceManager* m_resourceManager;				//!< リソースマネージャー
		MEGraphicPipeline* m_pipeline;								//!< パイプライン
		MEGraphicRenderTarget* m_renderTarget;						//!< レンダーターゲット
	};
}

#endif//__MugenEngine_GraphicLoadedImage__