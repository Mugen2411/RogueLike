//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderQueue__
#define __MugenEngine_GraphicRenderQueue__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "GraphicStruct.h"
#include <list>
#include <DirectXTex.h>

namespace mugen_engine
{
	class MEGraphicRenderQueue
	{
	public:
		static void Initialize(MEGraphicDevice& device);
		//! 描画を予約する
		static void ReserveRender(D3D12_VERTEX_BUFFER_VIEW* vbView, CONSTANT_DATA constData,
			ID3D12DescriptorHeap* textureHeap, int blendType);
		//! 予約した描画を行う
		static void RenderAll(MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
	private:
		struct RENDER_DATA
		{
			D3D12_VERTEX_BUFFER_VIEW* vertexBufferView;
			ID3D12DescriptorHeap* textureHeap;
			int blendType;
		};

		//! 指定したインデックスにCBVを構築する
		static void _CreateCbv(uint32_t index, const MEGraphicDevice& device);
		//! 定数バッファを確保する
		static void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_constantDescHeap;		//!< 定数用のディスクリプタヒープ
		static std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;//!< 定数バッファ
		static int m_currentReserved;												//!< 現在描画予約キューに入っている数
		static int m_maxReserve;													//!< 描画予約可能な最大数
		static std::vector<RENDER_DATA> m_reserveList;								//!< 描画予約キュー
		static uint32_t m_descriptorHeapIncrementSize;								//!< SRVとCBVにおけるディスクリプタヒープ上のサイズ
		static MEGraphicDevice* m_pDevice;											//!< デバイス
	};
}

#endif//__MugenEngine_GraphicRenderQueue__