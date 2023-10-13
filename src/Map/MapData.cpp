//! @file MapData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MapData.h"
#include "../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		width				マップの横幅
		@param[in]		height				マップの高さ
		@return			なし
	*//***********************************************************************/
	MRMapData::MRMapData(const int width, const int height) : m_width(width), m_height(height)
	{
		mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins.png", 8, 3);
		m_mapchipImg = &mugen_engine::MECore::GetIns().GetGraph("mapchip");
		m_mapData.resize(height);
		m_graphicData.resize(height);
		for (int y = 0; y < height; ++y)
		{
			m_mapData[y].resize(width);
			m_graphicData[y].resize(width);
		}
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapData[y][x] = rand() % 2;
			}
		}
		_ConvertGraphFromMap();
	}

	/**********************************************************************//**
		@brief			マップを描画する
		@param[in]		cameraX				マップの左上を合わせるX座標
		@param[in]		cameraY				マップの左上を合わせるY座標
		@return			なし
	*//***********************************************************************/
	void MRMapData::Render(const int cameraX, const int cameraY) const
	{
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapchipImg->DrawRotaGraph(cameraX + 16 + 32 * x, cameraY + 16 + 32 * y, 1.0f, 0.0f, 0.0f, m_graphicData[y][x]);
			}
		}
	}

	/**********************************************************************//**
		@brief			マップデータから表示に使うデータに変換する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRMapData::_ConvertGraphFromMap()
	{
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				int i = 0;
				if (m_mapData[y][x] == 1)
				{
					m_graphicData[y][x] = 16;
					continue;
				}
				if (x == m_width - 1 || m_mapData[y][x + 1] == 1)
				{
					i |= 1;
				}
				if (y == m_height - 1 || m_mapData[y + 1][x] == 1)
				{
					i |= 2;
				}
				if (x == 0 || m_mapData[y][x - 1] == 1)
				{
					i |= 4;
				}
				if (y == 0 || m_mapData[y - 1][x] == 1)
				{
					i |= 8;
				}
				m_graphicData[y][x] = i;
			}
		}
	}
}