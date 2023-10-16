//! @file GraphicLoadedImage.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicLoadedImage.h"
#include "GraphicGpuResourceManager.h"
#include "../Core.h"
#include "GraphicRenderQueue.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param		�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEImage::MEImage() :
		m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1), m_brightness(1.0f, 1.0f, 1.0f, 1.0f)
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		filepath			�摜�̃t�@�C���p�X
		@param[in]		device				�f�o�C�X
		@param[in]		xDivideNum			�������̕�����
		@param[in]		yDivideNum			�c�����̕�����
		@param[in]		cmdList				�R�}���h���X�g
		@param[in]		pipeline			�p�C�v���C��
		@param[in]		renderTarget		�����_�[�^�[�Q�b�g
		@return			�Ȃ�
	*//***********************************************************************/
	MEImage::MEImage(const std::wstring& filepath,
		MEGraphicDevice& device, size_t xDivideNum, size_t yDivideNum, MEGraphicCommandList& cmdList,
		MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget) :
		m_width(0), m_height(0), m_xDivideNum(xDivideNum), m_yDivideNum(yDivideNum),
		m_brightness(1.0f, 1.0f, 1.0f, 1.0f), m_pDevice(&device), m_pCmdList(&cmdList),
		m_pPipeline(&pipeline), m_pRenderTarget(&renderTarget), m_blendType(BLEND_TYPE::ALPHA)
	{
		DirectX::TexMetadata metadata = {};
		DirectX::ScratchImage scratchImg = {};
		DirectX::Image const* img = {};

		DirectX::LoadFromWICFile(filepath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratchImg);
		img = scratchImg.GetImage(0, 0, 0);

		m_width = metadata.width / xDivideNum;
		m_height = metadata.height / yDivideNum;

		m_vertices[0] = { { -static_cast<float>(m_width) / 2,-static_cast<float>(m_height) / 2, 0.0f }, { 0.0f, 1.0f } };
		m_vertices[1] = { {-static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2, 0.0f},{0.0f, 0.0f} };
		m_vertices[2] = { { static_cast<float>(m_width) / 2,-static_cast<float>(m_height) / 2, 0.0f},{1.0f, 1.0f} };
		m_vertices[3] = { { static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2, 0.0f},{1.0f, 0.0f} };

		m_resourceManager.Initialize(device, static_cast<UINT>(xDivideNum * yDivideNum));

		for (int index = 0; index < xDivideNum * yDivideNum; ++index)
		{
			m_vertices[0].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
				1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
			m_vertices[1].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
				1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
			m_vertices[2].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
				1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
			m_vertices[3].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
				1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
			m_resourceManager.UploadVertexData(index, m_vertices, 4);
		}

		m_resourceManager.CreateTextureBuffer(metadata, device);
		m_resourceManager.CreateSrv(img->format, device);

		m_resourceManager.UploadByCpu(img->pixels, img->rowPitch, img->height);

		//m_resourceManager.ResetUploadBuffer(img->rowPitch, img->height, device);
		//m_resourceManager.UploadDataToUploadBuffer(img->pixels, img->rowPitch, img->height);
		//m_resourceManager.UploadToGpu(metadata, img->rowPitch, img->format, *m_pCmdList);
	}

	/**********************************************************************//**
		@brief			�w�肵�����W�ɕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawGraph(int x, int y, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		if (x + m_width < 0) return;
		if (x - m_width > MECore::GetIns().GetWindowWidth()) return;
		if (y + m_height < 0) return;
		if (y - m_height > MECore::GetIns().GetWindowHeight()) return;
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().GetWindowWidth(),
			2.0f / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().GetWindowWidth() / 2) / MECore::GetIns().GetWindowWidth() * 2,
			static_cast<float>(-y + MECore::GetIns().GetWindowHeight() / 2) / MECore::GetIns().GetWindowHeight() * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = m_brightness;

		MEGraphicRenderQueue::ReserveRender(m_resourceManager.GetVertexBufferView(index), constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			���W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@param[in]		scale				�g�嗦
		@param[in]		angle				��]�p�x(���W�A��)
		@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawRotaGraph(int x, int y, float scale, float angle, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		if (x + m_width * scale < 0) return;
		if (x - m_width * scale > MECore::GetIns().GetWindowWidth()) return;
		if (y + m_height * scale < 0) return;
		if (y - m_height * scale > MECore::GetIns().GetWindowHeight()) return;

		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f * scale / MECore::GetIns().GetWindowWidth(),
			2.0f * scale / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().GetWindowWidth() / 2) / MECore::GetIns().GetWindowWidth() * 2,
			static_cast<float>(-y + MECore::GetIns().GetWindowHeight() / 2) / MECore::GetIns().GetWindowHeight() * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixRotationZ(angle);
		constData.brightness = m_brightness;

		MEGraphicRenderQueue::ReserveRender(m_resourceManager.GetVertexBufferView(index), constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			2�{���Z�Ŏw�肵�����W�ɕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawGraph2X(int x, int y, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		if (x + m_width * 2.0f < 0) return;
		if (x - m_width * 2.0f > MECore::GetIns().GetWindowWidth()) return;
		if (y + m_height * 2.0f < 0) return;
		if (y - m_height * 2.0f > MECore::GetIns().GetWindowHeight()) return;
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f * 2.0f / MECore::GetIns().GetWindowWidth(),
			2.0f * 2.0f / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x * 2 - MECore::GetIns().GetWindowWidth() / 2) / MECore::GetIns().GetWindowWidth() * 2,
			static_cast<float>(-y * 2 + MECore::GetIns().GetWindowHeight() / 2) / MECore::GetIns().GetWindowHeight() * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = m_brightness;

		MEGraphicRenderQueue::ReserveRender(m_resourceManager.GetVertexBufferView(index), constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			2�{���Z�ō��W�Ɗg�嗦�Ɖ�]�p�x���w�肵�ĕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@param[in]		y					�`�悷�钆�S��Y���W
		@param[in]		scale				�g�嗦
		@param[in]		angle				��]�p�x(���W�A��)
		@param[in]		index				�摜����������Ă���ꍇ�ǂ��`�悷�邩
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawRotaGraph2X(int x, int y, float scale, float angle, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}
		if (x + m_width * scale * 2.0f < 0) return;
		if (x - m_width * scale * 2.0f > MECore::GetIns().GetWindowWidth()) return;
		if (y + m_height * scale * 2.0f < 0) return;
		if (y - m_height * scale * 2.0f > MECore::GetIns().GetWindowHeight()) return;
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f * 2.0f * scale / MECore::GetIns().GetWindowWidth(),
			2.0f * 2.0f * scale / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x * 2 - MECore::GetIns().GetWindowWidth() / 2) / MECore::GetIns().GetWindowWidth() * 2,
			static_cast<float>(-y * 2 + MECore::GetIns().GetWindowHeight() / 2) / MECore::GetIns().GetWindowHeight() * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixRotationZ(angle);
		constData.brightness = m_brightness;

		MEGraphicRenderQueue::ReserveRender(m_resourceManager.GetVertexBufferView(index), constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			���R��4���_���w�肵�ĕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawModiGraph(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}

		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().GetWindowWidth(),
			2.0f / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixIdentity();
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = m_brightness;

		int ww = MECore::GetIns().GetWindowWidth() / 2;
		int wh = MECore::GetIns().GetWindowHeight() / 2;
		VERTEX_DATA tmp[4] = {};
		tmp[0].pos = DirectX::XMFLOAT3(static_cast<float>(x0 - ww), static_cast<float>(-y0 + wh), 0.0f);
		tmp[0].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		tmp[1].pos = DirectX::XMFLOAT3(static_cast<float>(x1 - ww), static_cast<float>(-y1 + wh), 0.0f);
		tmp[1].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		tmp[2].pos = DirectX::XMFLOAT3(static_cast<float>(x2 - ww), static_cast<float>(-y2 + wh), 0.0f);
		tmp[2].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		tmp[3].pos = DirectX::XMFLOAT3(static_cast<float>(x3 - ww), static_cast<float>(-y3 + wh), 0.0f);
		tmp[3].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));

		int vertexBufferIndex = 0;
		auto vbView = m_resourceManager.CreateAdditionalVertexBuffer(vertexBufferIndex, 4, *m_pDevice);
		m_resourceManager.UploadAdditionalVertexData(vertexBufferIndex, tmp, 4);

		MEGraphicRenderQueue::ReserveRender(vbView, constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			2�{���Z�Ŏ��R��4���_���w�肵�ĕ`��
		@param[in]		x					�`�悷�钆�S��X���W
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::DrawModiGraph2X(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, float priority, int index)
	{
		if (index >= m_xDivideNum * m_yDivideNum)
		{
			OutputDebugStringA("out of range");
			return;
		}

		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().GetWindowWidth(),
			2.0f / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixIdentity();
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = m_brightness;

		int ww = MECore::GetIns().GetWindowWidth() / 2;
		int wh = MECore::GetIns().GetWindowHeight() / 2;
		VERTEX_DATA tmp[4] = {};
		tmp[0].pos = DirectX::XMFLOAT3(static_cast<float>(x0 * 2 - ww), static_cast<float>(-y0 * 2 + wh), 0.0f);
		tmp[0].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		tmp[1].pos = DirectX::XMFLOAT3(static_cast<float>(x1 * 2 - ww), static_cast<float>(-y1 * 2 + wh), 0.0f);
		tmp[1].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));
		tmp[2].pos = DirectX::XMFLOAT3(static_cast<float>(x2 * 2 - ww), static_cast<float>(-y2 * 2 + wh), 0.0f);
		tmp[2].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum + 1));
		tmp[3].pos = DirectX::XMFLOAT3(static_cast<float>(x3 * 2 - ww), static_cast<float>(-y3 * 2 + wh), 0.0f);
		tmp[3].uv = DirectX::XMFLOAT2(1.0f / m_xDivideNum * (index % m_xDivideNum + 1),
			1.0f / m_yDivideNum * static_cast<int>(index / m_xDivideNum));

		int vertexBufferIndex = 0;
		auto vbView = m_resourceManager.CreateAdditionalVertexBuffer(vertexBufferIndex, 4, *m_pDevice);
		m_resourceManager.UploadAdditionalVertexData(vertexBufferIndex, tmp, 4);

		MEGraphicRenderQueue::ReserveRender(vbView, constData,
			&m_resourceManager, m_blendType, priority, m_pCmdList, m_pPipeline, m_pRenderTarget);
	}

	/**********************************************************************//**
		@brief			�摜�`�掞�̋P�x��ݒ�
		@param[in]		R					��
		@param[in]		G					��
		@param[in]		B					��
		@param[in]		A					�s�����x
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::SetBrightness(const float R, const float G, const float B, const float A)
	{
		m_brightness = DirectX::XMFLOAT4(R, G, B, A);
	}

	/**********************************************************************//**
		@brief			�摜�`�掞�̃u�����h�^�C�v��ݒ�
		@param[in]		blendType					�u�����h�^�C�v
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::SetBlendType(BLEND_TYPE blendType)
	{
		m_blendType = blendType;
	}

	/**********************************************************************//**
		@brief			�ǉ��̒��_�o�b�t�@�����Z�b�g
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MEImage::ResetAdditionalVertexBuffer()
	{
		m_resourceManager.ResetAdditionalVertexBuffer();
	}
}
