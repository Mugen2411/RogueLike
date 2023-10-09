//! @file GraphicCharacterRenderUnit.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicCharacterRenderUnit.h"
#include "GraphicGpuResourceManager.h"
#include "GraphicCommandList.h"
#include "GraphicPipeline.h"
#include "GraphicRenderTarget.h"
#include "../Core.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicCharacterUnit::MEGraphicCharacterUnit()
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		character			�e�N�X�`���ɕϊ����镶��
		@param[in]		fontData			�t�H���g
		@param[in]		hdc					�f�o�C�X�R���e�L�X�g
		@param[in]		device				�f�o�C�X
		@param[in]		cmdList				�R�}���h���X�g
		@param[in]		pipeline			�p�C�v���C��
		@param[in]		renderTarget		�����_�[�^�[�Q�b�g
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicCharacterUnit::MEGraphicCharacterUnit(const wchar_t character, HFONT fontData, HDC hdc,
		MEGraphicDevice& device, MEGraphicCommandList& cmdList, MEGraphicPipeline& pipeline, MEGraphicRenderTarget& renderTarget) :
		m_pCmdList(&cmdList), m_pPipeline(&pipeline), m_pRenderTarget(&renderTarget)
	{
		// �t�H���g�r�b�g�}�b�v�擾
		UINT code = character;
		const int gradFlag = GGO_GRAY4_BITMAP;
		// �K���̍ő�l
		int grad = 0;
		switch(gradFlag)
		{
			case GGO_GRAY2_BITMAP:
				grad = 4;
				break;
			case GGO_GRAY4_BITMAP:
				grad = 16;
				break;
			case GGO_GRAY8_BITMAP:
				grad = 64;
				break;
		}

		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		GLYPHMETRICS gm;
		CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
		DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
		BYTE* pMono = new BYTE[size];
		GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);

		//�t�H���g�̕��ƍ���
		m_width = gm.gmCellIncX;
		m_height = tm.tmHeight;

		std::vector<TexRGBA> textureData(m_width * m_height, TexRGBA { 0,0,0,0 });
		DirectX::TexMetadata metadata;
		metadata.width = m_width;
		metadata.height = m_height;
		metadata.dimension = DirectX::TEX_DIMENSION_TEXTURE2D;
		metadata.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		metadata.arraySize = 1;
		metadata.mipLevels = 1;
		metadata.depth = 1;

		// �t�H���g���̏�������
		// iOfs_x, iOfs_y : �����o���ʒu(����)
		// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
		// Level : ���l�̒i�K
		int iOfs_x = gm.gmptGlyphOrigin.x;
		int iOfs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
		int iBmp_w = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
		int iBmp_h = gm.gmBlackBoxY;
		int Level = grad + 1;

		for(size_t y = iOfs_y; y < iOfs_y + iBmp_h; y++)
		{
			for(size_t x = iOfs_x; x < iOfs_x + gm.gmBlackBoxX; x++)
			{
				textureData[x + m_width * y] = TexRGBA { 0xFF, 0xFF, 0xFF, static_cast<uint8_t>((255 * pMono[x - iOfs_x + iBmp_w * (y - iOfs_y)])
					/ (Level - 1)) };
			}
		}

		m_vertices[0] = { { 0.0f, -static_cast<float>(m_height), 0.0f }, { 0.0f, 1.0f } };
		m_vertices[1] = { { 0.0f, 0.0f, 0.0f},{0.0f, 0.0f} };
		m_vertices[2] = { { static_cast<float>(m_width), -static_cast<float>(m_height), 0.0f},{1.0f, 1.0f} };
		m_vertices[3] = { { static_cast<float>(m_width), 0.0f, 0.0f},{1.0f, 0.0f} };

		m_resourceManager.Initialize(device);
		m_resourceManager.CreateTextureBuffer(metadata, device);
		m_resourceManager.CreateSrv(metadata.format, device);

		m_resourceManager.ResetUploadBuffer(m_width * sizeof(TexRGBA), m_height, device);
		m_resourceManager.UploadDataToUploadBuffer(reinterpret_cast<uint8_t*>(textureData.data()), m_width * sizeof(TexRGBA), m_height);
		m_resourceManager.UploadToGpu(metadata, m_width * sizeof(TexRGBA), metadata.format, *m_pCmdList);
	}

	/**********************************************************************//**
		@brief			������`��
		@param[in]		x					�����X���W
		@param[in]		y					�����Y���W
		@param[in]		color				�����F
		@return			�Ȃ�
	*//***********************************************************************/
	void MEGraphicCharacterUnit::DrawCharacter(const int x, const int y, float color[4])
	{
		CONSTANT_DATA constData = {};
		constData.scaleMatrix = DirectX::XMMatrixScaling(2.0f / MECore::GetIns().GetWindowWidth(),
			2.0f / MECore::GetIns().GetWindowHeight(), 1.0f);
		constData.moveMatrix = DirectX::XMMatrixTranslation(
			static_cast<float>(x - MECore::GetIns().GetWindowWidth() / 2) / MECore::GetIns().GetWindowWidth() * 2,
			static_cast<float>(-y + MECore::GetIns().GetWindowHeight() / 2) / MECore::GetIns().GetWindowHeight() * 2, 0.0f);
		constData.rotateMatrix = DirectX::XMMatrixIdentity();
		constData.brightness = DirectX::XMFLOAT4 { color[0], color[1], color[2], color[3] };

		m_pRenderTarget->SetRenderBaseCommand(*m_pCmdList);
		m_pPipeline->SetPipelineState(0, *m_pCmdList);
		m_resourceManager.SetGpuResource(*m_pCmdList);

		m_pCmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_resourceManager.UploadVertexData(m_vertices, _countof(m_vertices));
		m_resourceManager.UploadConstantData(constData);
		m_resourceManager.SetRenderCommand(*m_pCmdList);

		m_pCmdList->Execute();
	}
}