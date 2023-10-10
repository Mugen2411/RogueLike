//! @file GraphicGpuResourceManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicGpuResourceManager__
#define __MugenEngine_GraphicGpuResourceManager__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicStruct.h"

#include <d3d12.h>
#include <DirectXMath.h>
#include <DirectXTex.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicGpuResourceManager
		@brief		GPU資源を管理するクラス
	*//***********************************************************************/
	class MEGraphicGpuResourceManager
	{
	public:
		//! コンストラクタ
		MEGraphicGpuResourceManager();
		//! 初期化
		void Initialize(const MEGraphicDevice& device);
		//! GPUリソースをコマンドリストに設定する
		void SetGpuResource(MEGraphicCommandList& cmdList);
		//! 頂点データをバッファに書き込む
		void UploadVertexData(VERTEX_DATA* vertices, size_t vertexNum);
		//! 定数バッファに書き込む
		void UploadConstantData(CONSTANT_DATA& constData);
		//! 描画対象としてセットする
		void SetRenderCommand(MEGraphicCommandList& cmdList);
		//! 指定したインデックスにフォーマットを参考にSRVを構築する
		void CreateSrv(const DXGI_FORMAT format,
			const MEGraphicDevice& device);
		//! テクスチャのバッファを作成する
		void CreateTextureBuffer(const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);
		//! アップロード用のバッファを再設定する
		void ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);
		//! アップロード用のバッファにデータを流し込む
		void UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);
		//! GPUにテクスチャデータをアップロードする
		void UploadToGpu(DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);
		//! CPUで転送する
		void UploadByCpu(uint8_t* srcData, size_t rowPitch, size_t height);
		//! 頂点バッファビューを取得
		D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView()
		{
			return &m_vertexBufferView;
		}
		//! テクスチャ用ヒープを取得
		ID3D12DescriptorHeap* GetTextureHeap()
		{
			return m_basicDescHeap.Get();
		}
	private:
		//! 定数バッファを確保する
		void _InitalizeConstantBuffer(const MEGraphicDevice& device);
		//! アライメントサイズを取得
		size_t _GetAlignmentedSize(size_t size, size_t alignment);
		//! 指定したインデックスにCBVを構築する
		void _CreateCbv(const MEGraphicDevice& device);
		//! テクスチャアップロード前のバリア設定
		void _SetBarrierBeforeUploadTexture(const MEGraphicCommandList& cmdList);
		//! 頂点バッファの作成
		void _CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device);

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< ディスクリプタヒープ
		uint32_t m_descriptorHeapIncrementSize;										//!< SRVとCBVにおけるディスクリプタヒープ上のサイズ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;						//!< テクスチャのバッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;					//!< 定数バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< アップロード用の中間バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;			//!< 頂点バッファ
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;								//!< 頂点バッファビュー
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__