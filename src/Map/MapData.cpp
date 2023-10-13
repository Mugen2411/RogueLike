//! @file MapData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MapData.h"
#include "../Engine/Core.h"
#include <queue>
#include <stack>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		width				マップの横幅
		@param[in]		height				マップの高さ
		@return			なし
	*//***********************************************************************/
	MRMapData::MRMapData(const int width, const int height, uint32_t seed) : m_width(width), m_height(height), m_random(seed)
	{
#ifdef _DEBUG
		mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins_DEBUG.png", 8, 3);
#else
		mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins.png", 8, 3);
#endif
		m_mapchipImg = &mugen_engine::MECore::GetIns().GetGraph("mapchip");
		m_font = &mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");
		m_mapData.resize(height);
		m_graphicData.resize(height);
		for (int y = 0; y < height; ++y)
		{
			m_mapData[y].resize(width);
			m_graphicData[y].resize(width);
		}
		_DivideRooms();
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
		const int chipW = 8;
		const int chipH = 16;
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapchipImg->DrawRotaGraph(cameraX + chipW / 2 + chipW * x, cameraY + chipH / 2 + chipW * y,
					static_cast<float>(chipW) / 32, 0.0f, 2.0f, m_graphicData[y][x]);
			}
		}
		float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		for (auto& i : m_roomIndex)
		{
			m_font->DrawFormatString(cameraX + i.x * chipW, cameraY + i.y * chipW, color, 1.0f, L"%d", i.index);
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

	/**********************************************************************//**
		@brief			マップデータを部屋割りする
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRMapData::_DivideRooms()
	{
		const int divide_margin = 11;
		const int room_margin = 2;
		const int room_minimum = 7;
		std::vector<ROOM_NODE> roomList;

		int xNum = m_random.GetRanged(max(3, m_width / divide_margin - 3), m_width / divide_margin);
		int yNum = m_random.GetRanged(max(3, m_height / divide_margin - 3), m_height / divide_margin);

		for (int y = 0; y < yNum; ++y)
		{
			for (int x = 0; x < xNum; ++x)
			{
				int r = m_random.GetRanged(0, 99);
				int u = 0;
				if (r > 70)
				{
					u = 1;
				}
				if (r > 30)
				{
					u = 2;
				}
				roomList.push_back(ROOM_NODE(m_width * x / xNum, m_height * y / yNum, m_width * (x + 1) / xNum, m_height * (y + 1) / yNum, u));
			}
		}

		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapData[y][x] = 1;
			}
		}

		for (int i = 0; i < roomList.size(); ++i)
		{
			if (roomList[i].usedFor == 0) continue;
			int offsetX = m_random.GetRanged(roomList[i].topX + room_margin, roomList[i].bottomX - room_margin - room_minimum);
			roomList[i].topX = offsetX;
			roomList[i].bottomX = m_random.GetRanged(offsetX + room_minimum, roomList[i].bottomX - room_margin);

			int offsetY = m_random.GetRanged(roomList[i].topY + room_margin, roomList[i].bottomY - room_margin - room_minimum);
			roomList[i].topY = offsetY;
			roomList[i].bottomY = m_random.GetRanged(offsetY + room_minimum, roomList[i].bottomY - room_margin);

			m_roomIndex.push_back(
				ROOM_INDEX((roomList[i].bottomX + roomList[i].topX) / 2, (roomList[i].bottomY + roomList[i].topY) / 2, i));
			for (int y = roomList[i].topY; y < roomList[i].bottomY; ++y)
			{
				for (int x = roomList[i].topX; x < roomList[i].bottomX; ++x)
				{
					m_mapData[y][x] = 0;
				}
			}
		}
	}
}