//! @file MapData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MapData.h"
#include "../Engine/Core.h"
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		width				マップの横幅
		@param[in]		height				マップの高さ
		@return			なし
	*//***********************************************************************/
	MRMapData::MRMapData(const int width, const int height, uint32_t seed) :
		m_width(width), m_height(height), m_random(seed), m_chipSize(32.0f)
	{
		mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins.png", 2, 1);
		mugen_engine::MECore::GetIns().LoadDivGraph("minimap", L"media/graphic/mapchip/minimap.png", 2, 1);
		m_mapchipImg = &mugen_engine::MECore::GetIns().GetGraph("mapchip");
		m_minimapImg = &mugen_engine::MECore::GetIns().GetGraph("minimap");
		m_minimapImg->SetBrightness(1.0f, 1.0f, 1.0f, 0.5f);
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
		@param[in]		camera				カメラ
		@return			なし
	*//***********************************************************************/
	void MRMapData::Render(const MRCamera& camera) const
	{
		const int chipW = 32;
		const int chipH = 64;
		const float priority[2] = { 2.0f, 1.0f };
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapchipImg->DrawRotaGraph2X(camera.GetAnchoredX(chipW / 2 + chipW * x),
					camera.GetAnchoredY(chipH / 2 + chipW * y),
					static_cast<float>(chipW) / 32, 0.0f, priority[m_graphicData[y][x]], m_graphicData[y][x]);
			}
		}
#ifdef _DEBUG
		float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		for (auto& i : m_roomIndex)
		{
			m_font->DrawFormatString(camera.GetAnchoredX(i.x * chipW),
				camera.GetAnchoredY(i.y * chipW), color, 1.0f, L"%d", i.index);
		}
#endif
	}

	/**********************************************************************//**
		@brief			ミニマップを描画する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRMapData::RenderMiniMap() const
	{
		for (auto& r : roomList)
		{
			if (r.usedFor != 1) continue;
			m_minimapImg->DrawModiGraph2X(r.topX, r.topY, r.bottomX, r.topY, r.topX, r.bottomY, r.bottomX, r.bottomY, -0.1f, 0);
		}
	}

	/**********************************************************************//**
		@brief			壁と物体の衝突を処理する
		@param[in]		transform			物体の位置速度情報
		@param[in]		size				物体の一辺の長さ
		@return			なし
	*//***********************************************************************/
	void MRMapData::HitWithWall(MRTransform& transform, const float size)
	{
		auto hitToChip = [&](float chipX, float chipY) {
			auto setU = [&]() {
				transform.SetY(chipY + m_chipSize / 2 + size);
				transform.SetVelocityY(0.0f);
				};
			auto setD = [&]() {
				transform.SetY(chipY - m_chipSize / 2 - size);
				transform.SetVelocityY(0.0f);
				};
			auto setR = [&]() {
				transform.SetX(chipX - m_chipSize / 2 - size);
				transform.SetVelocityX(0.0f);
				};
			auto setL = [&]() {
				transform.SetX(chipX + m_chipSize / 2 + size);
				transform.SetVelocityX(0.0f);
				};

			float nowX = transform.GetX();
			float nowY = transform.GetY();
			float nextX = transform.GetNextX();
			float nextY = transform.GetNextY();

			double max = (nowX + size) - (chipX - m_chipSize / 2),
				may = (nowY + size) - (chipY - m_chipSize / 2);
			double nax = (chipX + m_chipSize / 2) - (nowX - size),
				nay = (chipY + m_chipSize / 2) - (nowY - size);
			double _max = (nextX + size) - (chipX - m_chipSize / 2),
				_may = (nextY + size) - (chipY - m_chipSize / 2);
			double _nax = (chipX + m_chipSize / 2) - (nextX - size),
				_nay = (chipY + m_chipSize / 2) - (nextY - size);
			bool U = false, D = false, R = false, L = false;

			//カド同士の判定
			if (0 >= max && 0 >= may && _max > 0 && _may > 0)
			{
				if (_max >= _may)
				{
					//下にある
					D = true;
					setD();
				}
				else
				{
					//右にある
					R = true;
					setR();
				}
			}
			if (0 >= nax && 0 >= may && _nax > 0 && _may > 0)
			{
				if (_nax >= _may)
				{
					//下にある
					D = true;
					setD();
				}
				else
				{
					//左にある
					L = true;
					setL();
				}
			}
			if (0 >= max && 0 >= nay && _max > 0 && _nay > 0)
			{
				if (_max >= _nay)
				{
					//上にある
					U = true;
					setU();
				}
				else
				{
					//右にある
					R = true;
					setR();
				}
			}
			if (0 >= nax && 0 >= nay && _nax > 0 && _nay > 0)
			{
				if (_nax >= _nay)
				{
					//上にある
					U = true;
					setU();
				}
				else
				{
					//左にある
					L = true;
					setL();
				}
			}

			//上下左右の判定
			if (may > 0 && nay > 0)
			{
				if (_nax > 0 &&
					(nowX - size) > (chipX - m_chipSize / 2))
				{
					//左にある
					L = true;
					setL();
				}
				if (_max > 0 &&
					(chipX + m_chipSize / 2) > (nowX + size))
				{
					//右にある
					R = true;
					setR();
				}
			}
			if (max > 0 && nax > 0)
			{
				if (_nay > 0 &&
					(nowY - size) > (chipY - m_chipSize / 2))
				{
					//上にある
					U = true;
					setU();
				}
				if (_may > 0 &&
					(chipY + m_chipSize / 2) > (nowY + size))
				{
					//下にある
					D = true;
					setD();
				}
			}

			};

		int currentChipX = static_cast<int>((transform.GetX() - size) / m_chipSize);
		int currentChipY = static_cast<int>((transform.GetY() - size) / m_chipSize);

		for (int y = max(currentChipY - 3,0); y <= min(currentChipY + 3, m_height); ++y)
		{
			for (int x = max(currentChipX - 3, 0); x <= min(currentChipX + 3, m_width); ++x)
			{
				if (m_mapData[y][x] == 0) continue;
				hitToChip(x * m_chipSize + m_chipSize * 0.5f, y * m_chipSize + m_chipSize * 0.5f);
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
				/*int i = 0;
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
				}*/
				m_graphicData[y][x] = m_mapData[y][x];
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
		const int room_minimum = 6;
		const int divide_margin = room_minimum + room_margin * 2 + 4;
		const int radius_path = 1;
		//std::vector<ROOM_NODE> roomList;

		if (m_width < divide_margin * 3 || m_height < divide_margin * 3)
		{
			OutputDebugString(L"map size too small");
			return;
		}

		// 部屋の割り方を決める
		int xNum = m_random.GetRanged(max(3, m_width / divide_margin - 3), m_width / divide_margin);
		int yNum = m_random.GetRanged(max(3, m_height / divide_margin - 3), m_height / divide_margin);

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
		// subetenosetuzokujoukyouwohozonn
		std::vector<std::set<int>> globalConnect(xNum * yNum);
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
						globalConnect[cur].insert(cur - 1);
						globalConnect[cur - 1].insert(cur);
					}
				}
				if (x + 1 < xNum && connect[cur + 1] == -1)
				{
					reserve.push_back(cur + 1);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur + 1] = cur;
						globalConnect[cur].insert(cur + 1);
						globalConnect[cur + 1].insert(cur);
					}
				}
				if (y - 1 >= 0 && connect[cur - xNum] == -1)
				{
					reserve.push_back(cur - xNum);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur - xNum] = cur;
						globalConnect[cur].insert(cur - xNum);
						globalConnect[cur - xNum].insert(cur);
					}
				}
				if (y + 1 < yNum && connect[cur + xNum] == -1)
				{
					reserve.push_back(cur + xNum);
					if (m_random.GetRanged(0, 0) == 0)
					{
						connect[cur + xNum] = cur;
						globalConnect[cur].insert(cur + xNum);
						globalConnect[cur + xNum].insert(cur);
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
			else
			{
				globalConnect[connect[i]].insert(i);
				globalConnect[i].insert(connect[i]);
			}
		}

		makePathes();

		_SetStartPosition(roomList);

	}
	void MRMapData::_SetStartPosition(std::vector<ROOM_NODE>& rooms)
	{
		std::vector<int> roomIndices;
		for (int i = 0; i < rooms.size(); ++i)
		{
			roomIndices.push_back(i);
		}
		std::shuffle(roomIndices.begin(), roomIndices.end(), m_random.GetDevice());
		for (auto& r : roomIndices)
		{
			if (rooms[r].usedFor == 1)
			{
				m_startX = (rooms[r].topX + rooms[r].bottomX) / 2;
				m_startY = (rooms[r].topY + rooms[r].bottomY) / 2;
				break;
			}
		}
	}
}