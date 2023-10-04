//! @file GraphicPipeline.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicPipeline__
#define __MugenEngine_GraphicPipeline__

#include "GraphicDevice.h"

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicPipeline
		@brief		ブレンド等を含むパイプラインを管理するクラス
	*//***********************************************************************/
	class MEGraphicPipeline
	{
	public: 
		//! コンストラクタ
		MEGraphicPipeline();
		//! 初期化
		void Initialize(const MEGraphicDevice& device);
	private:
		//! バイトコード周りのエラー処理
		void _processBlobError(HRESULT result);

		Microsoft::WRL::ComPtr<ID3DBlob> m_vsBlob = nullptr;							//!< 頂点シェーダーのバイトコード
		Microsoft::WRL::ComPtr<ID3DBlob> m_psBlob = nullptr;							//!< ピクセルシェーダーのバイトコード
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorBlob = nullptr;						//!< バイトコード読み込みのエラーコード

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState = nullptr;		//!< パイプラインステート
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;		//!< ルートシグネチャ
	};
}

#endif//__MugenEngine_GraphicPipeline__