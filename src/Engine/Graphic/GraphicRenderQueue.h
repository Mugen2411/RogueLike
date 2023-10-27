//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderQueue__
#define __MugenEngine_GraphicRenderQueue__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicGpuResourceManager.h"
#include "GraphicStruct.h"
#include <deque>
#include <DirectXTex.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicRenderQueue
		@brief		描画待ちの画像を蓄えて処理するクラス
	*//***********************************************************************/
	class MEGraphicRenderQueue
	{
	public:
		/**********************************************************************//**
			@brief			初期化
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		static void Initialize(MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			描画を予約する
			@param[in]		vbView				頂点バッファビュー
			@param[in]		constData			定数バッファのデータ
			@param[in]		textureHeap			テクスチャのディスクリプタヒープ
			@param[in]		blendType			ブレンドタイプ
			@param[in]		priority			描画優先度
			@param[in]		cmdList				コマンドリスト
			@param[in]		pipeline			パイプライン
			@param[in]		renderTarget		レンダーターゲット
			@return			なし
		*//***********************************************************************/
		static void ReserveRender(const D3D12_VERTEX_BUFFER_VIEW vbView, const CONSTANT_DATA constData,
			MEGraphicGpuResourceManager* textureHeap, const int blendType, const float priority,
			MEGraphicCommandList* cmdList, MEGraphicPipeline* pipeline,
			MEGraphicRenderTarget* renderTarget);
		
		/**********************************************************************//**
			@brief			予約された描画を全部発火する
			@param[in]		cmdList				コマンドリスト
			@param[in]		pipeline			パイプライン
			@param[in]		renderTarget		レンダーターゲット
			@return			なし
		*//***********************************************************************/
		static void RenderAll(MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);

	private:
		/**********************************************************************//**
			@struct		RENDER_DATA
			@brief		四角形のポリゴンを一枚描画する単位
		*//***********************************************************************/
		struct RENDER_DATA
		{
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;			//!< 頂点バッファビュー
			MEGraphicGpuResourceManager* textureHeap;			//!< テクスチャのディスクリプタヒープ
			int blendType;										//!< ブレンドタイプ
			CONSTANT_DATA constData;							//!< 定数データ
			float priority;										//!< 描画優先度
			size_t order;										//!< 予約された順番
		};

		/**********************************************************************//**
			@brief			指定したインデックスに定数バッファビューを構築する
			@param[in]		index				生成時に割り当てられたインデックス
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		static void _CreateCbv(const uint32_t index, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			定数バッファを初期化する
			@param[in]		device			デバイス
			@return			なし
		*//***********************************************************************/
		static void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_constantDescHeap;			//!< 定数用のディスクリプタヒープ
		static std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;	//!< 定数バッファ
		static int m_maxReserve;														//!< 描画予約可能な最大数
		static std::deque<RENDER_DATA> m_reserveList;									//!< 描画予約キュー
		static std::vector<const RENDER_DATA*> m_reservePointerList;					//!< ソートに使うポインタの配列
		static uint32_t m_descriptorHeapIncrementSize;									//!< SRVとCBVにおけるディスクリプタヒープ上のサイズ
		static MEGraphicDevice* m_pDevice;												//!< デバイス
		static std::vector<CONSTANT_DATA*> m_pMapMatrix;								//!< マップされた定数バッファ
	};
}

#endif//__MugenEngine_GraphicRenderQueue__