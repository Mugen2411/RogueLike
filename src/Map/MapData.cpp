//! @file MapData.cpp
//! @note Copyright (c) Mugen_GameLab

#include "MapData.h"
#include "../Engine/Core.h"
#include "../Util/Constants.h"
#include "../Util/EventQueue.h"
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRMapData::MRMapData(): m_chipSize(32.0f), m_random(0)
	{
		mugen_engine::MECore::GetIns().LoadDivGraph("mapchip", L"media/graphic/mapchip/ruins.png", 3, 1);
		mugen_engine::MECore::GetIns().LoadDivGraph("minimap", L"media/graphic/mapchip/minimap.png", 4, 2);
		m_mapchipImg = &mugen_engine::MECore::GetIns().GetGraph("mapchip");
		m_minimapImg = &mugen_engine::MECore::GetIns().GetGraph("minimap");
		m_minimapImg->SetBrightness(1.0f, 1.0f, 1.0f, 1.0f);
		m_font = &mugen_engine::MECore::GetIns().GetFont("__mugen_engine_default__");
	}

	/**********************************************************************//**
		@brief			マップを生成する
		@param[in]		width				マップの横幅
		@param[in]		height				マップの高さ
		@param[in]		seed				シード値
		@param[in]		staticList			静止オブジェクトの管理者
		@return			なし
	*//***********************************************************************/
	void MRMapData::Construct(const int width, const int height, uint32_t seed, MRStaticObjectManager& staticList)
	{
		m_random.SetSeed(seed);

		m_width = width;
		m_height = height;

		m_mapData.resize(height);
		m_graphicData.resize(height);
		for (int y = 0; y < height; ++y)
		{
			m_mapData[y].resize(width);
			m_graphicData[y].resize(width);
		}
		m_roomIndex.clear();
		m_roomList.clear();
		m_regionList.clear();
		m_pathList.clear();

		_DivideRooms();
		_ConvertGraphFromMap();
		_SpawnTreasureBox(staticList);
	}

	/**********************************************************************//**
		@brief			マップを更新する
		@param[in]		プレイヤーの位置
		@return			なし
	*//***********************************************************************/
	void MRMapData::Update(const MRTransform& playerTransform)
	{
		int x = static_cast<int>(playerTransform.GetX() / m_chipSize);
		int y = static_cast<int>(playerTransform.GetY() / m_chipSize);
		size_t numRegion = m_regionList.size();
		for (size_t i = 0; i < numRegion; ++i)
		{
			if (m_regionList[i].usedFor == 0)continue;

			if (m_regionList[i].topX <= x && x <= m_regionList[i].bottomX &&
				m_regionList[i].topY <= y && y <= m_regionList[i].bottomY)
			{
				m_regionList[i].usedFor = 0;
			}
		}
	}

	/**********************************************************************//**
		@brief			マップを描画する
		@param[in]		camera				カメラ
		@return			なし
	*//***********************************************************************/
	void MRMapData::Render(const MRCamera& camera) const
	{
		const int chipW = 32;
		const int chipH = 32;
		const float priority[3] = 
		{ constants::render_priority::MAP_FLOOR, constants::render_priority::MAP_WALL, constants::render_priority::MAP_WALL};
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
		@param[in]		プレイヤーの位置
		@return			なし
	*//***********************************************************************/
	void MRMapData::RenderMiniMap(MRTransform& playerTransform,
		MRStaticObjectManager& staticList) const
	{
		int larger = max(m_width, m_height);

		m_minimapImg->DrawModiGraph2X(0, 0, constants::screen::left_margin, 0,
			0, constants::screen::height, constants::screen::left_margin, constants::screen::height,
			constants::render_priority::MINIMAP_BASE);

		m_minimapImg->DrawRotaGraph(static_cast<int>(playerTransform.GetX() * constants::screen::left_margin * 2 / m_chipSize / larger),
			static_cast<int>(playerTransform.GetY() * constants::screen::left_margin * 2 / m_chipSize / larger),
			max(constants::screen::left_margin * 2 * 0.25f / larger, 0.5f), 0.0f,
			constants::render_priority::MINIMAP_PLAYER, 3);
		std::vector<MRTransform> staticTransforms;
		staticList.GetTransforms(staticTransforms);
		for (auto& t : staticTransforms)
		{
			m_minimapImg->DrawRotaGraph(static_cast<int>(t.GetX() * constants::screen::left_margin * 2 / m_chipSize / larger),
				static_cast<int>(t.GetY() * constants::screen::left_margin * 2 / m_chipSize / larger),
				max(constants::screen::left_margin * 2 * 0.20f / larger, 0.4f), 0.0f,
				constants::render_priority::MINIMAP_TREASUREBOX, 5);
		}

		m_minimapImg->DrawRotaGraph(static_cast<int>(m_goalX * constants::screen::left_margin * 2 / larger),
			static_cast<int>(m_goalY * constants::screen::left_margin * 2 / larger),
			max(constants::screen::left_margin * 2 * 0.25f / larger, 0.5f), 0.0f, constants::render_priority::MINIMAP_TREASUREBOX, 6);

		for (auto& r : m_roomList)
		{
			if (r.usedFor == 1)
			{
				m_minimapImg->DrawModiGraph(
					r.topX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
					r.bottomX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
					r.topX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
					r.bottomX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
					constants::render_priority::MINIMAP_ROOM, 2);
			}
			else if (r.usedFor == 2)
			{
				m_minimapImg->DrawModiGraph(
					(r.topX - 1) * constants::screen::left_margin * 2 / larger, (r.topY - 1) * constants::screen::left_margin * 2 / larger,
					(r.bottomX + 1) * constants::screen::left_margin * 2 / larger, (r.topY - 1) * constants::screen::left_margin * 2 / larger,
					(r.topX - 1) * constants::screen::left_margin * 2 / larger, (r.bottomY + 1) * constants::screen::left_margin * 2 / larger,
					(r.bottomX + 1) * constants::screen::left_margin * 2 / larger, (r.bottomY + 1) * constants::screen::left_margin * 2 / larger,
					constants::render_priority::MINIMAP_PATH, 1);
			}
		}

		for (auto& r : m_pathList)
		{
			m_minimapImg->DrawModiGraph(
				r.topX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
				r.bottomX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
				r.topX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
				r.bottomX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
				constants::render_priority::MINIMAP_PATH, 1);
		}
		for (auto& r : m_regionList)
		{
			if (r.usedFor == 0) continue;
			m_minimapImg->DrawModiGraph(
				r.topX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
				r.bottomX * constants::screen::left_margin * 2 / larger, r.topY * constants::screen::left_margin * 2 / larger,
				r.topX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
				r.bottomX * constants::screen::left_margin * 2 / larger, r.bottomY * constants::screen::left_margin * 2 / larger,
				constants::render_priority::MINIMAP_DISCOVERED, 4);
		}
	}

	/**********************************************************************//**
		@brief			壁と物体の衝突を処理する
		@param[in]		transform			物体の位置速度情報
		@param[in]		size				物体の一辺の長さ
		@return			なし
	*//***********************************************************************/
	void MRMapData::HitWithWall(MRTransform& transform, const float size, MREventQueue& eventQueue)
	{
		auto hitToChip = [&](float chipX, float chipY, int chipID) {
			auto setU = [&]() {
				transform.SetY(chipY + m_chipSize / 2 + size + 2);
				transform.SetVelocityY(0.0f);
				};
			auto setD = [&]() {
				transform.SetY(chipY - m_chipSize / 2 - size - 2);
				transform.SetVelocityY(0.0f);
				};
			auto setR = [&]() {
				transform.SetX(chipX - m_chipSize / 2 - size - 2);
				transform.SetVelocityX(0.0f);
				};
			auto setL = [&]() {
				transform.SetX(chipX + m_chipSize / 2 + size + 2);
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

			if (U || D || R || L)
			{
				if(chipID == 2) eventQueue.Push(MREventQueue::EVENT_ID::SELECT_GOTO_NEXT_FLOOR, 0);
			}

			};

		int currentChipX = static_cast<int>((transform.GetX() - size) / m_chipSize);
		int currentChipY = static_cast<int>((transform.GetY() - size) / m_chipSize);

		for (int y = max(currentChipY - 3, 0); y <= min(currentChipY + 3, m_height); ++y)
		{
			for (int x = max(currentChipX - 3, 0); x <= min(currentChipX + 3, m_width); ++x)
			{
				if (m_mapData[y][x] == 0) continue;
				hitToChip(x * m_chipSize + m_chipSize * 0.5f, y * m_chipSize + m_chipSize * 0.5f, m_mapData[y][x]);
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
		const int room_minimum = 7;
		const int divide_margin = room_minimum + room_margin * 2 + 8;
		const int radius_path = 1;

		if (m_width < divide_margin * 3 || m_height < divide_margin * 3)
		{
			OutputDebugString(L"map size too small");
			return;
		}

		// 部屋の割り方を決める
		int xNum = m_random.GetRanged(max(3, m_width / divide_margin - 6), m_width / divide_margin);
		int yNum = m_random.GetRanged(max(3, m_height / divide_margin - 6), m_height / divide_margin);

		uint32_t yetElement = xNum * yNum;
		uint32_t yetRoom = static_cast<uint32_t>(yetElement * static_cast<float>(m_random.GetRanged(55, 85)) / 100.0f);
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
				assert(u != 0);
				m_roomList.push_back(ROOM_NODE(m_width * x / xNum, m_height * y / yNum, m_width * (x + 1) / xNum, m_height * (y + 1) / yNum, u));
				m_regionList.push_back(ROOM_NODE(m_width * x / xNum, m_height * y / yNum, m_width * (x + 1) / xNum, m_height * (y + 1) / yNum, 1));
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

					connect[cur - 1] = cur;
					globalConnect[cur].insert(cur - 1);
					globalConnect[cur - 1].insert(cur);
				}
				if (x + 1 < xNum && connect[cur + 1] == -1)
				{
					reserve.push_back(cur + 1);

					connect[cur + 1] = cur;
					globalConnect[cur].insert(cur + 1);
					globalConnect[cur + 1].insert(cur);
				}
				if (y - 1 >= 0 && connect[cur - xNum] == -1)
				{
					reserve.push_back(cur - xNum);

					connect[cur - xNum] = cur;
					globalConnect[cur].insert(cur - xNum);
					globalConnect[cur - xNum].insert(cur);
				}
				if (y + 1 < yNum && connect[cur + xNum] == -1)
				{
					reserve.push_back(cur + xNum);

					connect[cur + xNum] = cur;
					globalConnect[cur].insert(cur + xNum);
					globalConnect[cur + xNum].insert(cur);
				}
				std::shuffle(reserve.begin(), reserve.end(), m_random.GetDevice());
				for (auto& i : reserve)
				{
					st.push(i);
				}
				reserve.clear();
			}
		}

		assert(std::count(connect.cbegin(), connect.cend(), -1) == 0);

		// マップを壁で埋める
		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_mapData[y][x] = 1;
			}
		}

		for (int i = 0; i < m_roomList.size(); ++i)
		{
			if (m_roomList[i].usedFor == 0)
			{
				continue;
			}
			if (m_roomList[i].usedFor == 1)
			{
				// 部屋の大きさを区画内でランダムに決める
				int offsetX = m_random.GetRanged(m_roomList[i].topX + room_margin, m_roomList[i].bottomX - room_margin - room_minimum);
				m_roomList[i].topX = offsetX;
				m_roomList[i].bottomX = m_random.GetRanged(offsetX + room_minimum, m_roomList[i].bottomX - room_margin);

				int offsetY = m_random.GetRanged(m_roomList[i].topY + room_margin, m_roomList[i].bottomY - room_margin - room_minimum);
				m_roomList[i].topY = offsetY;
				m_roomList[i].bottomY = m_random.GetRanged(offsetY + room_minimum, m_roomList[i].bottomY - room_margin);
			}
			if (m_roomList[i].usedFor == 2)
			{
				// 交差点の位置を点で打つ
				int offsetX = m_random.GetRanged(m_roomList[i].topX + room_margin, m_roomList[i].bottomX - room_margin - room_minimum);
				m_roomList[i].topX = offsetX;
				m_roomList[i].bottomX = offsetX + 1;

				int offsetY = m_random.GetRanged(m_roomList[i].topY + room_margin, m_roomList[i].bottomY - room_margin - room_minimum);
				m_roomList[i].topY = offsetY;
				m_roomList[i].bottomY = offsetY + 1;
			}

			// デバッグ用部屋番号
			m_roomIndex.push_back(
				ROOM_INDEX((m_roomList[i].bottomX + m_roomList[i].topX) / 2, (m_roomList[i].bottomY + m_roomList[i].topY) / 2, i));

			// 部屋や交差点に当たる部分に穴をあける
			for (int y = m_roomList[i].topY; y < m_roomList[i].bottomY; ++y)
			{
				for (int x = m_roomList[i].topX; x < m_roomList[i].bottomX; ++x)
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
			for (int i = 0; i < m_roomList.size(); ++i)
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
					int beginX;
					int endX;
					int beginY;
					int endY;
					int wallX;
					if (m_roomList[i].topX < m_roomList[connect[i]].topX)	//左→右に接続
					{
						beginX = m_roomList[i].bottomX;
						endX = m_roomList[connect[i]].topX;

						if (m_roomList[i].usedFor == 2)
						{
							beginY = m_roomList[i].topY;
						}
						else
						{
							beginY = m_random.GetRanged(m_roomList[i].topY + radius_path + 1, m_roomList[i].bottomY - radius_path - 1);
						}
						if (m_roomList[connect[i]].usedFor == 2)
						{
							endY = m_roomList[connect[i]].topY;
						}
						else
						{
							endY = m_random.GetRanged(m_roomList[connect[i]].topY + radius_path + 1,
								m_roomList[connect[i]].bottomY - radius_path - 1);
						}
					}
					else
					{
						beginX = m_roomList[connect[i]].bottomX;
						endX = m_roomList[i].topX;

						if (m_roomList[connect[i]].usedFor == 2)
						{
							beginY = m_roomList[connect[i]].topY;
						}
						else
						{
							beginY = m_random.GetRanged(m_roomList[connect[i]].topY + radius_path + 1,
								m_roomList[connect[i]].bottomY - radius_path - 1);
						}
						if (m_roomList[i].usedFor == 2)
						{
							endY = m_roomList[i].topY;
						}
						else
						{
							endY = m_random.GetRanged(m_roomList[i].topY + radius_path + 1, m_roomList[i].bottomY - radius_path - 1);
						}
					}
					wallX = m_random.GetRanged(beginX + room_margin, endX - room_margin);

					m_pathList.push_back(ROOM_NODE(beginX - radius_path, beginY - radius_path, wallX, beginY + radius_path + 1, 2));
					for (int x = beginX - radius_path; x < wallX; ++x)
					{
						fill3X3(beginY, x);
					}

					m_pathList.push_back(ROOM_NODE(wallX, endY - radius_path, endX, endY + radius_path + 1, 2));
					for (int x = wallX; x < endX + radius_path; ++x)
					{
						fill3X3(endY, x);
					}

					m_pathList.push_back(ROOM_NODE(wallX - radius_path, min(beginY, endY) - radius_path, wallX + radius_path + 1, max(beginY, endY) + radius_path + 1, 2));
					for (int y = min(beginY, endY); y <= max(beginY, endY); ++y)
					{
						fill3X3(y, wallX);
					}
				}
				//接続先が縦にある時
				else if (fromX == toX)
				{
					int beginX;
					int endX;
					int beginY;
					int endY;
					int wallY;
					if (m_roomList[i].topY < m_roomList[connect[i]].topY)	//上→下に接続
					{
						beginY = m_roomList[i].bottomY;
						endY = m_roomList[connect[i]].topY;

						if (m_roomList[i].usedFor == 2)
						{
							beginX = m_roomList[i].topX;
						}
						else
						{
							beginX = m_random.GetRanged(m_roomList[i].topX + radius_path + 1, m_roomList[i].bottomX - radius_path - 1);
						}
						if (m_roomList[connect[i]].usedFor == 2)
						{
							endX = m_roomList[connect[i]].topX;
						}
						else
						{
							endX = m_random.GetRanged(m_roomList[connect[i]].topX + radius_path + 1,
								m_roomList[connect[i]].bottomX - radius_path - 1);
						}
					}
					else
					{
						beginY = m_roomList[connect[i]].bottomY;
						endY = m_roomList[i].topY;

						if (m_roomList[connect[i]].usedFor == 2)
						{
							beginX = m_roomList[connect[i]].topX;
						}
						else
						{
							beginX = m_random.GetRanged(m_roomList[connect[i]].topX + radius_path + 1,
								m_roomList[connect[i]].bottomX - radius_path - 1);
						}
						if (m_roomList[i].usedFor == 2)
						{
							endX = m_roomList[i].topX;
						}
						else
						{
							endX = m_random.GetRanged(m_roomList[i].topX + radius_path + 1, m_roomList[i].bottomX - radius_path - 1);
						}
					}
					wallY = m_random.GetRanged(beginY + room_margin, endY - room_margin);

					m_pathList.push_back(ROOM_NODE(beginX - radius_path, beginY - radius_path, beginX + radius_path + 1, wallY + radius_path, 2));
					for (int y = beginY - radius_path; y < wallY; ++y)
					{
						fill3X3(y, beginX);
					}

					m_pathList.push_back(ROOM_NODE(endX - radius_path, wallY, endX + radius_path + 1, endY, 2));
					for (int y = wallY; y < endY + radius_path; ++y)
					{
						fill3X3(y, endX);
					}

					m_pathList.push_back(ROOM_NODE(min(beginX, endX) - radius_path, wallY - radius_path,
						max(beginX, endX) + radius_path + 1, wallY + radius_path + 1, 2));
					for (int x = min(beginX, endX); x <= max(beginX, endX); ++x)
					{
						fill3X3(wallY, x);
					}
				}
			}
			};

		makePathes();

		for (int i = 0; i < m_roomList.size(); ++i)
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

		for (int i = 0; i < m_roomList.size(); ++i)
		{
			if (m_random.GetRanged(0, 5) != 0)
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

		// スタート地点とゴール地点を一番遠くになるように決める
		std::vector<int> distance(yNum * xNum, 999999);
		std::stack<int> st;
		st.push(m_random.GetRanged(0, yNum* xNum - 1));
		distance[st.top()] = 0;

		while (!st.empty())
		{
			int cur = st.top();
			st.pop();
			for (auto& i : globalConnect[cur])
			{

				if (distance[i] > distance[cur] + 1)
				{
					distance[i] = distance[cur] + 1;
					st.push(i);
				}
			}
		}
		int begin_idx = -1;
		int max_dist = 0;
		for (int i = 0; i < distance.size(); ++i)
		{
			if (m_roomList[i].usedFor != 1) continue;
			if (max_dist < distance[i])
			{
				max_dist = distance[i];
				begin_idx = i;
			}
		}

		for (auto& i : distance)
		{
			i = 999999;
		}

		st.push(begin_idx);
		distance[st.top()] = 0;

		while (!st.empty())
		{
			int cur = st.top();
			st.pop();
			for (auto& i : globalConnect[cur])
			{

				if (distance[i] > distance[cur] + 1)
				{
					distance[i] = distance[cur] + 1;
					st.push(i);
				}
			}
		}

		max_dist = 0;
		int end_idx = -1;
		for (int i = 0; i < distance.size(); ++i)
		{
			if (m_roomList[i].usedFor != 1) continue;
			if (max_dist < distance[i])
			{
				max_dist = distance[i];
				end_idx = i;
			}
		}

		_SetStartPosition(begin_idx);
		_SetGoalPosition(end_idx);
	}

	/**********************************************************************//**
		@brief			プレイヤーの初期位置を決定する
		@param			index				部屋番号
		@return			なし
	*//***********************************************************************/

	void MRMapData::_SetStartPosition(const size_t index)
	{
		m_startX = (m_roomList[index].topX + m_roomList[index].bottomX) / 2;
		m_startY = (m_roomList[index].topY + m_roomList[index].bottomY) / 2;
	}

	/**********************************************************************//**
		@brief			階段の位置を決定する
		@param			index				部屋番号
		@return			なし
	*//***********************************************************************/
	void MRMapData::_SetGoalPosition(const size_t index)
	{
		int startX = (m_roomList[index].topX + m_roomList[index].bottomX) / 2;
		int startY = (m_roomList[index].topY + m_roomList[index].bottomY) / 2;

		int x = 0;
		int y = 0;
		do
		{
			x = m_random.GetRanged(m_roomList[index].topX + 1, m_roomList[index].bottomX - 2);
			y = m_random.GetRanged(m_roomList[index].topY + 1, m_roomList[index].bottomY - 2);
		} while (x == startX && y == startY);

		m_mapData[y][x] = 2;
		m_goalX = x;
		m_goalY = y;
	}

	/**********************************************************************//**
		@brief			宝箱を設置する
		@param			staticList					固定オブジェクトのリスト
		@return			なし
	*//***********************************************************************/
	void MRMapData::_SpawnTreasureBox(MRStaticObjectManager& staticList)
	{
		for (auto& r : m_roomList)
		{
			if (r.usedFor != 1) continue;
			int base_solid = 7 * 7;
			int room_solid = (r.bottomX - r.topX) * (r.bottomY - r.topY);
			int num = static_cast<int>(std::sqrtf(static_cast<float>(room_solid) / base_solid) - 0.1f);
			std::vector<int> old_x;
			std::vector<int> old_y;
			for (int i = 0; i < num; ++i)
			{
				int x, y;
				do
				{
					x = m_random.GetRanged(r.topX + 1, r.bottomX - 2);
					y = m_random.GetRanged(r.topY + 1, r.bottomY - 2);
				} while ((std::count(old_x.cbegin(), old_x.cend(), x) != 0 && std::count(old_y.cbegin(), old_y.cend(), y) != 0) ||
					m_mapData[y][x] != 0);

				staticList.Register(std::make_unique<MRTresureBox>((x + 0.5f) * m_chipSize, (y + 0.5f) * m_chipSize,
					static_cast<MRTresureBox::MRRarity>(m_random.GetRanged(0, 3)), m_random.Get()));
				old_x.push_back(x);
				old_y.push_back(y);
			}
		}
	}
}