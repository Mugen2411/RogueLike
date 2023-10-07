//! @file GraphicLoadedImage.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicLoadedImage.h"
#include "GraphicGpuResourceManager.h"
#include "../Core.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param		�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage() :
		m_index(0), m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1), m_brightness(1.0f, 1.0f, 1.0f, 1.0f)
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		index				�摜�ǂݍ��ݎ��̃C���f�b�N�X
		@param[in]		width				�摜�̉���
		@param[in]		height				�摜�̍���
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage(uint32_t index, size_t width, size_t height,
		MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager,
		MEGraphicPipeline* pipeline, MEGraphicRenderTarget* renderTarget) :
		m_index(index), m_width(width), m_height(height), m_xDivideNum(1), m_yDivideNum(1),
		m_vertices {
		{{-static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{0.0f, 1.0f}},
		{{-static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{0.0f, 0.0f}},
		{{ static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{1.0f, 1.0f}},
		{{ static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{1.0f, 0.0f}},
		}, m_brightness(1.0f, 1.0f, 1.0f, 1.0f), m_cmdList(cmdList), m_resourceManager(resourceManager),
		m_pipeline(pipeline), m_renderTarget(renderTarget)
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		index				�摜�ǂݍ��ݎ��̃C���f�b�N�X
		@param[in]		width				�摜�̉���
		@param[in]		height				�摜�̍���
		@param[in]		xDivideNum			�������̕�����
		@param[in]		yDivideNum			�c�����̕�����
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage(uint32_t index, size_t width, size_t height, size_t xDivideNum, size_t yDivideNum,
		MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager,
		MEGraphicPipeline* pipeline, MEGraphicRenderTarget* renderTarget) :
		m_index(index), m_width(width), m_height(height), m_xDivideNum(xDivideNum), m_yDivideNum(yDivideNum),
		m_vertices {
		{{-static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{0.0f, 1.0f}},
		{{-static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{0.0f, 0.0f}},
		{{ static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{1.0f, 1.0f}},
		{{ static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{1.0f, 0.0f}},
		}, m_cmdList(cmdList), m_resourceManager(resourceManager), m_pipeline(pipeline), m_renderTarget(renderTarget)
	{}

	/**********************************************************************//**
		@brief			�w�肵�����W�ɕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicLoadedImage::DrawGraph(int x, int y, int index)
	{
		if(index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		m_vertices[0].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		m_vertices[1].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		m_vertices[2].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		m_vertices[3].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().m_windowWidth,
			2.0f / MECore::GetIns().m_windowHeight, 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().m_windowWidth / 2) / MECore::GetIns().m_windowWidth * 2,
			static_cast<float>(-y + MECore::GetIns().m_windowHeight / 2) / MECore::GetIns().m_windowHeight * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = m_brightness;

		m_renderTarget->SetRenderBaseCommand(*m_cmdList);
		m_pipeline->SetPipelineState(0, *m_cmdList);
		m_resourceManager->SetGpuResource(m_index, *m_cmdList);

		m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager->UploadVertexData(m_vertices, _countof(m_vertices));
		m_resourceManager->UploadConstantData(m_index, constData);
		m_resourceManager->SetRenderCommand(*m_cmdList);

		m_cmdList->Execute();
	}

	/**********************************************************************//**
		@brief			���W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@param[in]		scale				�g�嗦
		@param[in]		angle				��]�p�x(���W�A��)
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicLoadedImage::DrawRotaGraph(int x, int y, float scale, float angle, int index)
	{
		if(index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		m_vertices[0].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		m_vertices[1].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		m_vertices[2].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		m_vertices[3].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f * scale / MECore::GetIns().m_windowWidth,
			2.0f * scale / MECore::GetIns().m_windowHeight, 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().m_windowWidth / 2) / MECore::GetIns().m_windowWidth * 2,
			static_cast<float>(-y + MECore::GetIns().m_windowHeight / 2) / MECore::GetIns().m_windowHeight * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixRotationZ(angle);
		constData.brightness = m_brightness;

		m_renderTarget->SetRenderBaseCommand(*m_cmdList);
		m_pipeline->SetPipelineState(0, *m_cmdList);
		m_resourceManager->SetGpuResource(m_index, *m_cmdList);

		m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager->UploadVertexData(m_vertices, _countof(m_vertices));
		m_resourceManager->UploadConstantData(m_index, constData);
		m_resourceManager->SetRenderCommand(*m_cmdList);

		m_cmdList->Execute();
	}

	/**********************************************************************//**
		@brief			�摜�`�掞�̋P�x��ݒ�
		@param[in]		R					��
		@param[in]		G					��
		@param[in]		B					��
		@param[in]		A					�s�����x
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicLoadedImage::SetBrightness(const float R, const float G, const float B, const float A)
	{
		m_brightness = DirectX::XMFLOAT4(R, G, B, A);
	}
}
