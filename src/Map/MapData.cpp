//! @file MapData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MapData.h"
#include "../Engine/Core.h"
#include <queue>
#include <stack>
#include <algorithm>

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
		const int chipW = 32;
		const int chipH = 64;
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapchipImg->DrawRotaGraph2X(chipW / 2 + chipW * x - cameraX, chipH / 2 + chipW * y - cameraY,
					static_cast<float>(chipW) / 32, 0.0f, 2.0f, m_graphicData[y][x]);
			}
		}
#ifdef _DEBUG
		float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		for (auto& i : m_roomIndex)
		{
			m_font->DrawFormatString(i.x * chipW - cameraX, i.y * chipW - cameraY, color, 1.0f, L"%d", i.index);
		}
#endif
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
		const int room_margin = 3;
		const int room_minimum = 9;
		const int divide_margin = room_minimum + room_margin * 2 + 2;
		const int radius_path = 1;
		std::vector<ROOM_NODE> roomList;

		if (m_width < divide_margin * 2 || m_height < divide_margin * 2)
		{
			OutputDebugString(L"map size too small");
			return;
		}

		// 部屋の割り方を決める
		int xNum = m_random.GetRanged(max(2, m_width / divide_margin - 3), m_width / divide_margin);
		int yNum = m_random.GetRanged(max(2, m_height / divide_margin - 3), m_height / divide_margin);

		uint32_t yetElement = xNum * yNum;
		uint32_t yetRoom = static_cast<uint32_t>(yetElement * static_cast<float>(m_random.GetRanged(6, 8)) / 10.0f);
		for (int y = 0; y < yNum; ++y)
		{
			for (int x = 0; x < xNum; ++x)
			{
				int u = 0;
				if (m_random.GetRanged(0, yetElement) <= yetRoom)
				{
					u = 1;
					--yetRoom;
				}
				else
				{
					u = 2;
				}
				--yetElement;
				roomList.push_back(ROOM_NODE(m_width * x / xNum, m_height * y / yNum, m_width * (x + 1) / xNum, m_height * (y + 1) / yNum, u));
			}
		}

		// 部屋の繋がり方を決める
		std::vector<int> connect(xNum * yNum, -1);
		{
			std::stack<int> st;
			std::vector<int> reserve;
			st.push(m_random.GetRanged(0, yNum * xNum - 1));
			while (!st.empty())
			{
				int cur = st.top();
				st.pop();
				int x = cur % xNum;
				int y = cur / xNum;
				
				if (x - 1 >= 0 && connect[cur - 1] == -1)
				{
					reserve.push_back(cur - 1);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur - 1] = cur;
					}
				}
				if (x + 1 < xNum && connect[cur + 1] == -1)
				{
					reserve.push_back(cur + 1);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur + 1] = cur;
					}
				}
				if (y - 1 >= 0 && connect[cur - xNum] == -1)
				{
					reserve.push_back(cur - xNum);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur - xNum] = cur;
					}
				}
				if (y + 1 < yNum && connect[cur + xNum] == -1)
				{
					reserve.push_back(cur + xNum);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur + xNum] = cur;
					}
				}
				std::shuffle(reserve.begin(), reserve.end(), m_random.GetDevice());
				for (auto& i : reserve)
				{
					st.push(i);
				}
				reserve.clear();
			}
		}

		// マップを壁で埋める
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapData[y][x] = 1;
			}
		}

		for (int i = 0; i < roomList.size(); ++i)
		{
			if (roomList[i].usedFor == 0)
			{
				continue;
			}
			if (roomList[i].usedFor == 1)
			{
				// 部屋の大きさを区画内でランダムに決める
				int offsetX = m_random.GetRanged(roomList[i].topX + room_margin, roomList[i].bottomX - room_margin - room_minimum);
				roomList[i].topX = offsetX;
				roomList[i].bottomX = m_random.GetRanged(offsetX + room_minimum, roomList[i].bottomX - room_margin);

				int offsetY = m_random.GetRanged(roomList[i].topY + room_margin, roomList[i].bottomY - room_margin - room_minimum);
				roomList[i].topY = offsetY;
				roomList[i].bottomY = m_random.GetRanged(offsetY + room_minimum, roomList[i].bottomY - room_margin);
			}
			if (roomList[i].usedFor == 2)
			{
				// 交差点の位置を点で打つ
				int offsetX = m_random.GetRanged(roomList[i].topX + room_margin, roomList[i].bottomX - room_margin - room_minimum);
				roomList[i].topX = offsetX;
				roomList[i].bottomX = offsetX + 1;

				int offsetY = m_random.GetRanged(roomList[i].topY + room_margin, roomList[i].bottomY - room_margin - room_minimum);
				roomList[i].topY = offsetY;
				roomList[i].bottomY = offsetY + 1;
			}

			// デバッグ用部屋番号
			m_roomIndex.push_back(
				ROOM_INDEX((roomList[i].bottomX + roomList[i].topX) / 2, (roomList[i].bottomY + roomList[i].topY) / 2, i));

			// 部屋や交差点に当たる部分に穴をあける
			for (int y = roomList[i].topY; y < roomList[i].bottomY; ++y)
			{
				for (int x = roomList[i].topX; x < roomList[i].bottomX; ++x)
				{
					m_mapData[y][x] = 0;
				}
			}
		}

		auto fill3X3 = [&](int Y, int X) {
			for (int y = max(0, Y - radius_path); y <= min(Y + radius_path, m_height - 1); ++y)
			{
				for (int x = max(0, X - radius_path); x <= min(X + radius_path, m_width - 1); ++x)
				{
					m_mapData[y][x] = 0;
				}
			}
			};
		auto makePathes = [&]() {
			for (int i = 0; i < roomList.size(); ++i)
			{
				if (connect[i] == -1)continue;
				// 通路に穴をあける
				int fromX = i % xNum;
				int fromY = i / xNum;
				int toX = connect[i] % xNum;
				int toY = connect[i] / xNum;

				//接続先が横にある時
				if (fromY == toY)
				{
					int wallX = (fromX > toX) ? m_random.GetRanged(roomList[connect[i]].bottomX + room_margin, roomList[i].topX - room_margin) :
						m_random.GetRanged(roomList[i].bottomX - room_margin, roomList[connect[i]].topX + room_margin);
					int beginY = (roomList[i].bottomY - roomList[i].topY == 1) ? roomList[i].topY :
						m_random.GetRanged(roomList[i].topY + radius_path, roomList[i].bottomY - radius_path - 1);
					int endY = (roomList[connect[i]].bottomY - roomList[connect[i]].topY == 1) ? roomList[connect[i]].topY :
						m_random.GetRanged(roomList[connect[i]].topY + radius_path, roomList[connect[i]].bottomY - radius_path - 1);
					for (int x = min(roomList[connect[i]].bottomX - radius_path, wallX); x < max(roomList[connect[i]].bottomX - radius_path, wallX); ++x)
					{
						fill3X3(endY, x);
					}
					for (int x = min(wallX, roomList[i].topX + radius_path); x < max(wallX, roomList[i].topX + radius_path); ++x)
					{
						fill3X3(beginY, x);
					}
					for (int y = min(beginY, endY); y <= max(beginY, endY); ++y)
					{
						fill3X3(y, wallX);
					}
				}
				//接続先が縦にある時
				if (fromX == toX)
				{
					int wallY = (fromY > toY) ? m_random.GetRanged(roomList[connect[i]].bottomY + room_margin, roomList[i].topY - room_margin) :
						m_random.GetRanged(roomList[i].bottomY - room_margin, roomList[connect[i]].topY + room_margin);
					int beginX = (roomList[i].bottomX - roomList[i].topX == 1) ? roomList[i].topX :
						m_random.GetRanged(roomList[i].topX + radius_path, roomList[i].bottomX - radius_path - 1);
					int endX = (roomList[connect[i]].bottomX - roomList[connect[i]].topX == 1) ? roomList[connect[i]].topX :
						m_random.GetRanged(roomList[connect[i]].topX + radius_path, roomList[connect[i]].bottomX - radius_path - 1);
					for (int y = min(roomList[connect[i]].bottomY - radius_path, wallY); y < max(roomList[connect[i]].bottomY - radius_path, wallY); ++y)
					{
						fill3X3(y, endX);
					}
					for (int y = min(wallY, roomList[i].topY + radius_path); y < max(wallY, roomList[i].topY + radius_path); ++y)
					{
						fill3X3(y, beginX);
					}
					for (int x = min(beginX, endX); x <= max(beginX, endX); ++x)
					{
						fill3X3(wallY, x);
					}
				}
			}
			};

		makePathes();

		for (int i = 0; i < roomList.size(); ++i)
		{
			int x = i % xNum;
			int y = i / xNum;
			std::vector<int> reserve;
			if (x - 1 >= 0)
			{
				reserve.push_back(i - 1);
			}
			if (x + 1 < xNum)
			{
				reserve.push_back(i + 1);
			}
			if (y - 1 >= 0 && connect[i - xNum] == -1)
			{
				reserve.push_back(i - xNum);
			}
			if (y + 1 < yNum && connect[i + xNum] == -1)
			{
				reserve.push_back(i + xNum);
			}
			std::shuffle(reserve.begin(), reserve.end(), m_random.GetDevice());
			for (auto& r : reserve)
			{
				if (connect[i] != r && connect[connect[r]] != i)
				{
					connect[i] = r;
					break;
				}
			}
			reserve.clear();
		}

		for (int i = 0; i < roomList.size(); ++i)
		{
			if (m_random.GetRanged(0, 7) != 0)
			{
				connect[i] = -1;
			}
		}

		makePathes();
	}
}