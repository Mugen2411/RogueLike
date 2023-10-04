#include "GraphicPipeline.h"
//! @file GraphicPipeline.cpp
//! @note Copyright (c) Mugen_GameLab

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
	void MEGraphicPipeline::Initialize(const MEGraphicDevice& device)
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
		_processBlobError(result);
		result = device.GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(m_rootSignature.ReleaseAndGetAddressOf()));
	}

	/**********************************************************************//**
		@brief			バイトコード周りのエラー処理
		@param			result				読み込み時のエラーコード
		@return			なし
	*//***********************************************************************/
	void MEGraphicPipeline::_processBlobError(HRESULT result)
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
}