//! @file GraphicPipeline.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicPipeline.h"

#include <fstream>

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MEGraphicPipeline::MEGraphicPipeline()
	{}

	/**********************************************************************//**
		@brief			初期化
		@param[in]		device			デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::Initialize(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize)
	{
		_LoadShader();
		_CreateRootSignarure(device);
		_CreatePipelineState(device, inputLayout, layoutSize);
	}

	/**********************************************************************//**
		@brief			バイトコード周りのエラー処理
		@param			result				読み込み時のエラーコード
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::_ProcessBlobError(HRESULT result)
	{
		if(SUCCEEDED(result))
		{
			return;
		}
		if(result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("ファイルが見当たりません");
			return;
		}
		std::string errstr;
		errstr.resize(m_errorBlob->GetBufferSize());
		std::copy_n(reinterpret_cast<char*>(m_errorBlob->GetBufferPointer()), m_errorBlob->GetBufferSize(), errstr.begin());
		errstr += '\n';
		::OutputDebugStringA(errstr.c_str());
	}

	/**********************************************************************//**
		@brief			ルートシグネチャの作成
		@param			device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::_CreateRootSignarure(const MEGraphicDevice& device)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr;
		//サンプラー
		D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		//ディスクリプタレンジ
		D3D12_DESCRIPTOR_RANGE descTblRange[2] = {};
		//テクスチャ用
		descTblRange[0].NumDescriptors = 1;
		descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descTblRange[0].BaseShaderRegister = 0;
		descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//定数用
		descTblRange[1].NumDescriptors = 1;
		descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		descTblRange[1].BaseShaderRegister = 0;
		descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//ルートパラメーター
		D3D12_ROOT_PARAMETER rootparam = {};
		//テクスチャ用
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootparam.DescriptorTable.pDescriptorRanges = descTblRange;
		rootparam.DescriptorTable.NumDescriptorRanges = 2;
		//ルートシグネチャ
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		rootSignatureDesc.pParameters = &rootparam;
		rootSignatureDesc.NumParameters = 1;
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
		auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
			rootSigBlob.ReleaseAndGetAddressOf(), m_errorBlob.ReleaseAndGetAddressOf());
		_ProcessBlobError(result);
		result = device.GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(m_rootSignature.ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			シェーダーの読み込み
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::_LoadShader()
	{
		//頂点シェーダー
		{
			std::ifstream ifs("BasicVertexShader.cso", std::ios_base::in | std::ios_base::binary);
			if(ifs.fail())
			{
				OutputDebugStringA("VS Load Error\n");
				return;
			}
			ifs.seekg(0, std::ios::end);
			size_t size = ifs.tellg();
			ifs.seekg(0, std::ios::beg);
			m_vsBlob.resize(size);
			ifs.read(m_vsBlob.data(), size);
		}

		//ピクセルシェーダー
		{
			std::ifstream ifs("BasicPixelShader.cso", std::ios_base::in | std::ios_base::binary);
			if(ifs.fail())
			{
				OutputDebugStringA("PS Load Error\n");
				return;
			}

			ifs.seekg(0, std::ios::end);
			size_t size = ifs.tellg();
			ifs.seekg(0, std::ios::beg);
			m_psBlob.resize(size);
			ifs.read(m_psBlob.data(), size);
		}
	}

	/**********************************************************************//**
		@brief			パイプラインステートの作成
		@param			device				デバイス
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::_CreatePipelineState(const MEGraphicDevice& device, const D3D12_INPUT_ELEMENT_DESC inputLayout[], const int layoutSize)
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
		//ルートシグネチャ
		gpipeline.pRootSignature = m_rootSignature.Get();
		//シェーダー設定
		gpipeline.VS.pShaderBytecode = m_vsBlob.data();
		gpipeline.VS.BytecodeLength = m_vsBlob.size();
		gpipeline.PS.pShaderBytecode = m_psBlob.data();
		gpipeline.PS.BytecodeLength = m_psBlob.size();
		//サンプルマスク
		gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		//ラスタライザーステート
		gpipeline.RasterizerState.MultisampleEnable = false;
		gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		gpipeline.RasterizerState.DepthClipEnable = true;
		//ブレンドステート
		gpipeline.BlendState.AlphaToCoverageEnable = false;
		gpipeline.BlendState.IndependentBlendEnable = false;

		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
		renderTargetBlendDesc.BlendEnable = true;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;

		gpipeline.BlendState.RenderTarget[0] = renderTargetBlendDesc;
		//入力レイアウト
		gpipeline.InputLayout.pInputElementDescs = inputLayout;
		gpipeline.InputLayout.NumElements = layoutSize;
		gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		//レンダーターゲット
		gpipeline.NumRenderTargets = 1;
		gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		//アンチエイリアス
		gpipeline.SampleDesc.Count = 1;
		gpipeline.SampleDesc.Quality = 0;

		auto result = device.GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(m_pipelineState[0].ReleaseAndGetAddressOf()));

		//加算ブレンド
		renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlend = D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlend = D3D12_BLEND_ONE;

		gpipeline.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		result = device.GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(m_pipelineState[1].ReleaseAndGetAddressOf()));

		//減算ブレンド
		renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_SUBTRACT;
		renderTargetBlendDesc.SrcBlend = D3D12_BLEND_ONE;
		renderTargetBlendDesc.DestBlend = D3D12_BLEND_ONE;

		gpipeline.BlendState.RenderTarget[0] = renderTargetBlendDesc;

		result = device.GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(m_pipelineState[2].ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			パイプラインステートの設定
		@param			type				描画タイプ(0=透過・1=加算・2=減算)
		@param			cmdList				コマンドリスト
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::SetPipelineState(const int type, MEGraphicCommandList& cmdList)
	{
		cmdList.GetCommandList()->SetPipelineState(m_pipelineState[type].Get());
		cmdList.GetCommandList()->SetGraphicsRootSignature(m_rootSignature.Get());
	}
}