//! @file GraphicGpuResourceManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicGpuResourceManager__
#define __MugenEngine_GraphicGpuResourceManager__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"
#include "GraphicLoadedImage.h"
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
		//! 画像を読み込む
		MEGraphicLoadedImage LoadGraph(const std::wstring& filepath, const MEGraphicDevice& device,
			MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! 画像を分割して読み込む
		MEGraphicLoadedImage LoadDivGraph(const std::wstring& filepath, size_t xDivideNum, size_t yDivideNum,
			const MEGraphicDevice& device, MEGraphicCommandList& cmdList,
			MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget);
		//! GPUリソースをコマンドリストに設定する
		void SetGpuResource(const uint32_t index, MEGraphicCommandList& cmdList);
		//! 頂点データをバッファに書き込む
		void UploadVertexData(VERTEX_DATA* vertices, size_t vertexNum);
		//! 定数バッファに書き込む
		void UploadConstantData(const uint32_t index, CONSTANT_DATA& constData);
		//! 描画対象としてセットする
		void SetRenderCommand(MEGraphicCommandList& cmdList);
	private:
		//! 定数バッファを確保する
		void _InitalizeConstantBuffer(uint32_t index, const MEGraphicDevice& device);
		//! アライメントサイズを取得
		size_t _GetAlignmentedSize(size_t size, size_t alignment);
		//! シェーダーリソースビューとコンスタントバッファビューを生成しても良いインデックスを返す
		uint32_t _GetShaderResourceIndex();
		//! 指定したインデックスにフォーマットを参考にSRVを構築する
		void _CreateSrv(uint32_t index, const DXGI_FORMAT format,
			const MEGraphicDevice& device);
		//! 指定したインデックスにCBVを構築する
		void _CreateCbv(uint32_t index, const MEGraphicDevice& device);
		//! テクスチャのバッファを作成する
		void _CreateTextureBuffer(const uint32_t index,
			const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);
		//! アップロード用のバッファを再設定する
		void _ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);
		//! アップロード用のバッファにデータを流し込む
		void _UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);
		//! GPUにテクスチャデータをアップロードする
		void _UploadToGpu(uint32_t index, DirectX::TexMetadata& metadata, size_t rowPitch, DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);
		//! テクスチャアップロード前のバリア設定
		void _SetBarrierBeforeUploadTexture(uint32_t index, const MEGraphicCommandList& cmdList);
		//! 頂点バッファの作成
		void _CreateVertexBuffer(size_t vertexNum, const MEGraphicDevice& device);

		uint32_t m_currentIndex = 0;												//!< 現在割り当てられている画像枚数
		uint32_t m_maxResourceView = 1024;											//!< 割り当てられる画像枚数の最大値
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< ディスクリプタヒープ
		uint32_t m_descriptorHeapIncrementSize;										//!< SRVとCBVにおけるディスクリプタヒープ上のサイズ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_textureBuffers;		//!< テクスチャのバッファ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_constantBuffers;		//!< 定数バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< アップロード用の中間バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;			//!< 頂点バッファ
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;								//!< 頂点バッファビュー
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__