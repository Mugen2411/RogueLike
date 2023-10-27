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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEImage();

		/**********************************************************************//**
			@brief			コンストラクタ
			@param[in]		filepath			画像のファイルパス
			@param[in]		device				デバイス
			@param[in]		xDivideNum			横方向の分割数
			@param[in]		yDivideNum			縦方向の分割数
			@param[in]		cmdList				コマンドリスト
			@param[in]		pipeline			パイプライン
			@param[in]		renderTarget		レンダーターゲット
			@return			なし
		*//***********************************************************************/
		MEImage(const std::wstring& filepath, MEGraphicDevice& device, size_t xDivideNum, size_t yDivideNum,
			MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

		/**********************************************************************//**
			@enum		BLEND_TYPE
			@brief		画像の合成方式
		*//***********************************************************************/
		enum BLEND_TYPE
		{
			ALPHA = 0, ADD, SUB
		};

		/**********************************************************************//**
			@brief			指定した座標に描画
			@param[in]		x					描画する中心のX座標
			@param[in]		y					描画する中心のY座標
			@param[in]		index				画像が分割されている場合どれを描画するか
			@return			なし
		*//***********************************************************************/
		void DrawGraph(const int x, const int y, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			座標と拡大率と回転角度を指定して描画
			@param[in]		x					描画する中心のX座標
			@param[in]		y					描画する中心のY座標
			@param[in]		scale				拡大率
			@param[in]		angle				回転角度(ラジアン)
			@param[in]		priority			描画優先度
			@param[in]		index				画像が分割されている場合どれを描画するか
			@return			なし
		*//***********************************************************************/
		void DrawRotaGraph(const int x, const int y, const float scale, const float angle, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			2倍換算で指定した座標に描画
			@param[in]		x					描画する中心のX座標
			@param[in]		y					描画する中心のY座標
			@param[in]		priority			描画優先度
			@param[in]		index				画像が分割されている場合どれを描画するか
			@return			なし
		*//***********************************************************************/
		void DrawGraph2X(const int x, const int y, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			2倍換算で座標と拡大率と回転角度を指定して描画
			@param[in]		x					描画する中心のX座標
			@param[in]		y					描画する中心のY座標
			@param[in]		scale				拡大率
			@param[in]		angle				回転角度(ラジアン)
			@param[in]		priority			描画優先度
			@param[in]		index				画像が分割されている場合どれを描画するか
			@return			なし
		*//***********************************************************************/
		void DrawRotaGraph2X(const int x, const int y, const float scale, const float angle,
			const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			自由に4頂点を指定して描画
			@param[in]		x0					X座標
			@param[in]		y0					Y座標
			@param[in]		x1					X座標
			@param[in]		y1					Y座標
			@param[in]		x2					X座標
			@param[in]		y2					Y座標
			@param[in]		x3					X座標
			@param[in]		y3					Y座標
			@param[in]		priority			描画優先度
			@param[in]		index				インデックス
			@return			なし
		*//***********************************************************************/
		void DrawModiGraph(const int x0, const int y0, const int x1, const int y1,
			const int x2, const int y2, const int x3, const int y3, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			自由に4頂点を指定して描画
			@param[in]		x0					X座標
			@param[in]		y0					Y座標
			@param[in]		x1					X座標
			@param[in]		y1					Y座標
			@param[in]		x2					X座標
			@param[in]		y2					Y座標
			@param[in]		x3					X座標
			@param[in]		y3					Y座標
			@param[in]		priority			描画優先度
			@param[in]		index				インデックス
			@return			なし
		*//***********************************************************************/
		void DrawModiGraph2X(const int x0, const int y0, const int x1, const int y1,
			const int x2, const int y2, const int x3, const int y3, const float priority, const int index = 0);

		/**********************************************************************//**
			@brief			画像描画時の輝度を設定
			@param[in]		R					赤
			@param[in]		G					緑
			@param[in]		B					青
			@param[in]		A					不透明度
			@return			なし
		*//***********************************************************************/
		void SetBrightness(const float R, const float G, const float B, const float A);

		/**********************************************************************//**
			@brief			画像描画時のブレンドタイプを設定
			@param[in]		blendType					ブレンドタイプ
			@return			なし
		*//***********************************************************************/
		void SetBlendType(const BLEND_TYPE blendType);

		/**********************************************************************//**
			@brief			追加の頂点バッファをリセット
			@param			なし
			@return			なし
		*//***********************************************************************/
		void ResetAdditionalVertexBuffer();
		
	private:
		size_t m_width;												//!< 画像の横幅
		size_t m_height;											//!< 画像の高さ
		size_t m_xDivideNum;										//!< 横方向の分割数
		size_t m_yDivideNum;										//!< 縦方向の分割数
		VERTEX_DATA m_vertices[4];									//!< 板ポリゴンとして表示するための頂点
		DirectX::XMFLOAT4 m_brightness;								//!< 輝度ベクトル
		BLEND_TYPE m_blendType;										//!< ブレンドタイプ
		MEGraphicDevice* m_pDevice;									//!< デバイス
		MEGraphicCommandList* m_pCmdList;							//!< コマンドリスト
		MEGraphicGpuResourceManager m_resourceManager;				//!< リソースマネージャー
		MEGraphicPipeline* m_pPipeline;								//!< パイプライン
		MEGraphicRenderTarget* m_pRenderTarget;						//!< レンダーターゲット
	};
}

#endif//__MugenEngine_GraphicLoadedImage__