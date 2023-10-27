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
#include <list>

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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicGpuResourceManager();

		/**********************************************************************//**
			@brief			初期化
			@param[in]		device				デバイス
			@param[in]		numVertexBuffer		頂点バッファの数
			@return			なし
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const UINT numVertexBuffer);

		/**********************************************************************//**
			@brief			描画時にディスクリプタヒープ等をコマンドリストに設定する
			@param[in]		cmdList					コマンドリスト
			@return			なし
		*//***********************************************************************/
		void SetGpuResource(MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			頂点データをバッファに書き込む
			@param[in]		index						インデックス
			@param[in]		vertices					頂点データの先頭のポインタ
			@param[in]		vertexNum					頂点の数
			@return			なし
		*//***********************************************************************/
		void UploadVertexData(const uint32_t index, VERTEX_DATA* vertices, const size_t vertexNum);

		/**********************************************************************//**
			@brief			定数バッファに書き込む
			@param[in]		constData					定数データ
			@return			なし
		*//***********************************************************************/
		void UploadConstantData(CONSTANT_DATA& constData);

		/**********************************************************************//**
			@brief			シェーダーリソースビューを構築する
			@param[in]		format				画像のフォーマット
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		void CreateSrv(const DXGI_FORMAT format, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			テクスチャのバッファを作成する
			@param[in]		metadata			画像のメタデータ
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		void CreateTextureBuffer(const DirectX::TexMetadata& metadata, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			アップロード用のバッファを再設定する
			@param[in]		rowPitch			画像の一行辺りのデータサイズ
			@param[in]		height				画像の高さ
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		void ResetUploadBuffer(const size_t rowPitch, const size_t height, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			中間バッファにデータをアップロードする
			@param[in]		srcData			画像の生データへのポインタ
			@param[in]		rowPitch		画像の一行辺りのデータサイズ
			@param[in]		height			画像の高さ
			@return			なし
		*//***********************************************************************/
		void UploadDataToUploadBuffer(uint8_t* srcData, const size_t rowPitch, const size_t height);

		/**********************************************************************//**
			@brief			テクスチャデータを転送する
			@param[in]		metadata					画像のメタデータ
			@param[in]		rowPitch					画像データの行単位のサイズ
			@param[in]		format						画像データのフォーマット
			@param[in]		cmdList						コマンドリスト
			@return			なし
		*//***********************************************************************/
		void UploadToGpu(DirectX::TexMetadata& metadata, const size_t rowPitch, const DXGI_FORMAT format,
			MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			CPUを用いてデータをアップロードする
			@param[in]		srcData			画像の生データへのポインタ
			@param[in]		rowPitch		画像の一行辺りのデータサイズ
			@param[in]		height			画像の高さ
			@return			なし
		*//***********************************************************************/
		void UploadByCpu(uint8_t* srcData, size_t rowPitch, size_t height);

		/**********************************************************************//**
			@brief			頂点バッファビューを取得
			@param[in]		index			インデックス
			@return			なし
		*//***********************************************************************/
		D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView(const uint32_t index)
		{
			return m_vertexBufferView[index];
		}

		/**********************************************************************//**
			@brief			テクスチャヒープを取得する
			@param			なし
			@return			なし
		*//***********************************************************************/
		ID3D12DescriptorHeap* GetTextureHeap()
		{
			return m_basicDescHeap.Get();
		}

		/**********************************************************************//**
			@brief			頂点バッファを作成する
			@param[in]		vertexNum					頂点の数(もし3D描画に対応するつもりならこれは画像の枚数だけ必要)
			@param[in]		device						デバイス
			@return			なし
		*//***********************************************************************/
		void CreateVertexBuffer(const size_t vertexNum, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			追加の頂点バッファを作成する
			@param[out]		vertexBufferIndex			追加された頂点バッファのインデックスを格納するバッファ
			@param[in]		vertexNum					頂点の数(もし3D描画に対応するつもりならこれは画像の枚数だけ必要)
			@param[in]		device						デバイス
			@return			なし
		*//***********************************************************************/
		D3D12_VERTEX_BUFFER_VIEW CreateAdditionalVertexBuffer(int& vertexBufferIndex, const size_t vertexNum, const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			追加の頂点データをバッファに書き込む
			@param[in]		index						インデックス
			@param[in]		vertices					頂点データの先頭のポインタ
			@param[in]		vertexNum					頂点の数
			@return			なし
		*//***********************************************************************/
		void UploadAdditionalVertexData(const uint32_t index, VERTEX_DATA* vertices, const size_t vertexNum);

		/**********************************************************************//**
			@brief			追加の頂点バッファをリセットする
			@param			なし
			@return			なし
		*//***********************************************************************/
		void ResetAdditionalVertexBuffer() {
			m_currerntAdditionalVertexBufferViewIndex = 0;
		}

	private:
		/**********************************************************************//**
			@brief			定数バッファを初期化する
			@param[in]		device			デバイス
			@return			なし
		*//***********************************************************************/
		void _InitalizeConstantBuffer(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief	アライメントに揃える
			@param size			元のサイズ
			@param alignment		アライメントサイズ
			@return				アライメントを揃えたサイズ
		*//***********************************************************************/
		size_t _GetAlignmentedSize(size_t size, size_t alignment);

		/**********************************************************************//**
			@brief			指定したインデックスに定数バッファビューを構築する
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		void _CreateCbv(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			テクスチャデータを転送する直前にバリアを設定する
			@param[in]		cmdList						コマンドリスト
			@return			なし
		*//***********************************************************************/
		void _SetBarrierBeforeUploadTexture(const MEGraphicCommandList& cmdList);

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_basicDescHeap = nullptr;		//!< ディスクリプタヒープ
		uint32_t m_descriptorHeapIncrementSize;										//!< SRVとCBVにおけるディスクリプタヒープ上のサイズ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;						//!< テクスチャのバッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;					//!< 定数バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadBuffer = nullptr;			//!< アップロード用の中間バッファ
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_vertexBuffer;			//!< 頂点バッファ
		std::vector<D3D12_VERTEX_BUFFER_VIEW> m_vertexBufferView;					//!< 頂点バッファビュー
		UINT m_numVertexBuffer;														//!< 頂点バッファの数
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_additionalVertexBuffer;	//!< 追加の頂点バッファ
		UINT m_numAdditionalVertexBuffer;											//!< 追加の頂点バッファの数
		UINT m_currerntAdditionalVertexBufferViewIndex;								//!< 次に割り当てる追加頂点バッファビュー
	};
}

#endif//__MugenEngine_GraphicGpuResourceManager__