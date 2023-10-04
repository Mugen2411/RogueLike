//! @file GraphicPipeline.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicPipeline.h"

#include <fstream>

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicPipeline::MEGraphicPipeline()
	{}

	/**********************************************************************//**
		@brief			������
		@param[in]		device			�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicPipeline::Initialize(const MEGraphicDevice& device)
	{
		_LoadShader();
		_CreateRootSignarure(device);
	}

	/**********************************************************************//**
		@brief			�o�C�g�R�[�h����̃G���[����
		@param			result				�ǂݍ��ݎ��̃G���[�R�[�h
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicPipeline::_ProcessBlobError(HRESULT result)
	{
		if(SUCCEEDED(result))
		{
			return;
		}
		if(result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("�t�@�C������������܂���");
			return;
		}
		std::string errstr;
		errstr.resize(m_errorBlob->GetBufferSize());
		std::copy_n(reinterpret_cast<char*>(m_errorBlob->GetBufferPointer()), m_errorBlob->GetBufferSize(), errstr.begin());
		errstr += '\n';
		::OutputDebugStringA(errstr.c_str());
	}

	/**********************************************************************//**
		@brief			���[�g�V�O�l�`���̍쐬
		@param			device				�f�o�C�X
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicPipeline::_CreateRootSignarure(const MEGraphicDevice& device)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr;
		//�T���v���[
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
		//�f�B�X�N���v�^�����W
		D3D12_DESCRIPTOR_RANGE descTblRange[2] = {};
		//�e�N�X�`���p
		descTblRange[0].NumDescriptors = 1;
		descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descTblRange[0].BaseShaderRegister = 0;
		descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//�萔�p
		descTblRange[1].NumDescriptors = 1;
		descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		descTblRange[1].BaseShaderRegister = 0;
		descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//���[�g�p�����[�^�[
		D3D12_ROOT_PARAMETER rootparam = {};
		//�e�N�X�`���p
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootparam.DescriptorTable.pDescriptorRanges = descTblRange;
		rootparam.DescriptorTable.NumDescriptorRanges = 2;
		//���[�g�V�O�l�`��
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
		@brief			�V�F�[�_�[�̓ǂݍ���
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicPipeline::_LoadShader()
	{
		//���_�V�F�[�_�[
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

		//�s�N�Z���V�F�[�_�[
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
}