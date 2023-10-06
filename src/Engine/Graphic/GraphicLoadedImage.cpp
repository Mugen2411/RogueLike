//! @file GraphicLoadedImage.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicLoadedImage.h"
#include "GraphicGpuResourceManager.h"
#include "../Core.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param		なし
		@return			なし
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage() :
		m_index(0), m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1)
	{}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		index				画像読み込み時のインデックス
		@param[in]		width				画像の横幅
		@param[in]		height				画像の高さ
		@return			なし
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
		}, m_cmdList(cmdList), m_resourceManager(resourceManager), m_pipeline(pipeline), m_renderTarget(renderTarget)
	{}

	/**********************************************************************//**
		@brief			指定した座標に描画
		@param[in]		x					描画する中心のX座標
		@param[in]		y					描画する中心のY座標
		@return			なし
	*//***********************************************************************/
	void MEGraphicLoadedImage::DrawGraph(int x, int y)
	{
		DirectX::XMMATRIX screenScale = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().m_windowWidth,
			2.0f / MECore::GetIns().m_windowHeight, 1.0f);
		DirectX::XMMATRIX moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().m_windowWidth / 2) / MECore::GetIns().m_windowWidth * 2,
			static_cast<float>(-y + MECore::GetIns().m_windowHeight / 2) / MECore::GetIns().m_windowHeight * 2, 0.0f);
		m_matrix = screenScale * moveMatrix;

		m_renderTarget->SetRenderBaseCommand(*m_cmdList);
		m_pipeline->SetPipelineState(0, *m_cmdList);
		m_resourceManager->SetGpuResource(m_index, *m_cmdList);

		m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager->UploadVertexData(m_vertices, _countof(m_vertices), *m_cmdList);
		m_resourceManager->UploadConstantData(m_index, m_matrix, *m_cmdList);
		m_resourceManager->SetRenderCommand(*m_cmdList);

		m_cmdList->Execute();
	}

	/**********************************************************************//**
		@brief			座標と拡大率と回転角度を指定して描画
		@param[in]		x					描画する中心のX座標
		@param[in]		y					描画する中心のY座標
		@param[in]		scale				拡大率
		@param[in]		angle				回転角度(ラジアン)
		@return			なし
	*//***********************************************************************/
	void MEGraphicLoadedImage::DrawRotaGraph(int x, int y, float scale, float angle)
	{
		DirectX::XMMATRIX screenScale = DirectX::XMMatrixScaling(2.0f * scale / MECore::GetIns().m_windowWidth,
			2.0f * scale / MECore::GetIns().m_windowHeight, 1.0f);
		DirectX::XMMATRIX moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().m_windowWidth / 2) / MECore::GetIns().m_windowWidth * 2,
			static_cast<float>(-y + MECore::GetIns().m_windowHeight / 2) / MECore::GetIns().m_windowHeight * 2, 0.0f);
		DirectX::XMMATRIX rotateMatrix = DirectX::XMMatrixRotationZ(angle);
		m_matrix = rotateMatrix * screenScale * moveMatrix;

		m_renderTarget->SetRenderBaseCommand(*m_cmdList);
		m_pipeline->SetPipelineState(0, *m_cmdList);
		m_resourceManager->SetGpuResource(m_index, *m_cmdList);

		m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager->UploadVertexData(m_vertices, _countof(m_vertices), *m_cmdList);
		m_resourceManager->UploadConstantData(m_index, m_matrix, *m_cmdList);
		m_resourceManager->SetRenderCommand(*m_cmdList);

		m_cmdList->Execute();
	}
}
