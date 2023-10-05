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
		m_index(0), m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1)
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		index				�摜�ǂݍ��ݎ��̃C���f�b�N�X
		@param[in]		width				�摜�̉���
		@param[in]		height				�摜�̍���
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage(uint32_t index, size_t width, size_t height,
		MEGraphicCommandList* cmdList, MEGraphicGpuResourceManager* resourceManager, MEGraphicPipeline* pipeline) :
		m_index(index), m_width(width), m_height(height), m_xDivideNum(1), m_yDivideNum(1),
		m_vertices {
		{{-static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{0.0f, 1.0f}},
		{{-static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{0.0f, 0.0f}},
		{{ static_cast<float>(width) / 2,-static_cast<float>(height) / 2, 0.0f},{1.0f, 1.0f}},
		{{ static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0.0f},{1.0f, 0.0f}},
		}, m_cmdList(cmdList), m_resourceManager(resourceManager), m_pipeline(pipeline)
	{}

	/**********************************************************************//**
		@brief			�w�肵�����W�ɕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicLoadedImage::DrawGraph(int x, int y)
	{
		static DirectX::XMMATRIX screenScale = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().m_windowWidth,
			2.0f / MECore::GetIns().m_windowHeight, 1.0f);
		DirectX::XMMATRIX moveMatrix = DirectX::XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), 0.0f);
		m_matrix = moveMatrix * screenScale;
		
		m_pipeline->SetPipelineState(0, *m_cmdList);
		m_resourceManager->SetGpuResource(m_index, *m_cmdList);

		m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager->UploadVertexData(m_vertices, _countof(m_vertices), *m_cmdList);
		m_resourceManager->UploadConstantData(m_index, m_matrix, *m_cmdList);
		m_resourceManager->SetRenderCommand(*m_cmdList);

		m_cmdList->Execute();
	}
}
