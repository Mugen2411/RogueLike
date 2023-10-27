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
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MEGraphicPipeline();

		/**********************************************************************//**
			@brief			初期化
			@param[in]		device			デバイス
			@param[in]		inputLayout			入力レイアウト
			@param[in]		layoutSize			レイアウトのサイズ
			@return			なし
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);

		/**********************************************************************//**
			@brief			パイプラインステートの設定
			@param[in]		type				描画タイプ(0=透過・1=加算・2=減算)
			@param			cmdList				コマンドリスト
			@return			なし
		*//***********************************************************************/
		void SetPipelineState(const int type, MEGraphicCommandList& cmdList);

	private:
		/**********************************************************************//**
			@brief			バイトコード周りのエラー処理
			@param[in]		result				読み込み時のエラーコード
			@return			なし
		*//***********************************************************************/
		void _ProcessBlobError(const HRESULT result);
		
		/**********************************************************************//**
			@brief			ルートシグネチャの作成
			@param[in]		device				デバイス
			@return			なし
		*//***********************************************************************/
		void _CreateRootSignarure(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			シェーダーの読み込み
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _LoadShader();

		/**********************************************************************//**
			@brief			パイプラインステートの作成
			@param[in]		device				デバイス
			@param[in]		inputLayout			入力レイアウト
			@param[in]		layoutSize			レイアウトのサイズ
			@return			なし
		*//***********************************************************************/
		void _CreatePipelineState(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize);

		std::vector<char> m_vsBlob;													//!< 頂点シェーダーのバイトコード
		std::vector<char> m_psBlob;													//!< ピクセルシェーダーのバイトコード
		Microsoft::WRL::ComPtr<ID3DBlob> m_errorBlob = nullptr;						//!< バイトコード読み込みのエラーコード

		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState[3] = { nullptr };		//!< パイプラインステート
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;		//!< ルートシグネチャ
	};
}

#endif//__MugenEngine_GraphicPipeline__