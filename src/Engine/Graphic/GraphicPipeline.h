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
		void _ProcessBlobError(HRESULT result);
		//! ルートシグネチャの作成
		void _CreateRootSignarure(const MEGraphicDevice& device);
		//! シェーダーの読み込み
		void _LoadShader();

		std::vector<char> m_vsBlob;													//!< 頂点シェーダーのバイトコード
		std::vector<char> m_psBlob;													//!< ピクセルシェーダーのバイトコード
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorBlob = nullptr;						//!< バイトコード読み込みのエラーコード

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState = nullptr;		//!< パイプラインステート
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;		//!< ルートシグネチャ
	};
}

#endif//__MugenEngine_GraphicPipeline__