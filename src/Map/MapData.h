//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include "../Engine/Graphic/GraphicFontData.h"
#include "../util/Camera.h"
#include "../util/Random.h"
#include "../util/Transform.h"
#include "../Static/StaticObjectInterface.h"
#include "../Static/TreasureBox.h"
#include "../Static/StaticObjectManager.h"
#include "../Mover/Enemy/EnemyManager.h"
#include <vector>
#include <memory>
#include <set>

namespace magica_rogue
{
	class MREventQueue;
	/**********************************************************************//**
		@class		MRMapData
		@brief		マップデータを扱うクラス
	*//***********************************************************************/
	class MRMapData
	{
	public:
		/**********************************************************************//**
			@brief			コンストラクタ
			@param			なし
			@return			なし
		*//***********************************************************************/
		MRMapData();
		
		/**********************************************************************//**
			@brief			マップを生成する
			@param[in]		width				マップの横幅
			@param[in]		height				マップの高さ
			@param[in]		seed				シード値
			@param[in]		staticList			静止オブジェクトの管理者
			@param[in]		enemyManager		敵の管理者
			@return			なし
		*//***********************************************************************/
		void Construct(const int width, const int height, uint32_t seed, MRStaticObjectManager& staticList, MREnemyManager& enemyManager);

		/**********************************************************************//**
			@brief			マップを更新する
			@param[in]		playerTransform			プレイヤーの位置
			@return			なし
		*//***********************************************************************/
		void Update(const MRTransform& playerTransform);

		/**********************************************************************//**
			@brief			マップを描画する
			@param[in]		camera				カメラ
			@return			なし
		*//***********************************************************************/
		void Render(const MRCamera& camera) const;

		/**********************************************************************//**
			@brief			ミニマップを描画する
			@param[in]		playerTransform			プレイヤーの位置
			@param[in]		staticList				静止オブジェクトの管理者
			@return			なし
		*//***********************************************************************/
		void RenderMiniMap(MRTransform& playerTransform, MRStaticObjectManager& staticList)const;

		/**********************************************************************//**
			@brief			プレイヤーの初期位置を設定
			@param[out]		playerTransform			プレイヤーの位置
			@return			なし
		*//***********************************************************************/
		void SetPlayerPosition(MRTransform& playerTransform) {
			playerTransform.SetPosition(m_startX * 32.0f + 16.0f, m_startY * 32.0f + 16.0f);
			m_pPlayerTransform = &playerTransform;
		}

		/**********************************************************************//**
			@brief			壁とプレイヤーの衝突を処理する
			@param[in]		transform			プレイヤーの位置速度情報
			@param[in]		size				プレイヤーの一辺の長さ
			@param			eventQueue			イベントキュー
			@return			なし
		*//***********************************************************************/
		void HitWallWithPlayer(MRTransform& transform, const float size, MREventQueue& eventQueue);
		
		/**********************************************************************//**
			@brief			壁と敵の衝突を処理する
			@param[in]		transform			敵の位置速度情報
			@param[in]		size				敵の一辺の長さ
			@return			なし
		*//***********************************************************************/
		void HitWallWithEnemy(MRTransform& transform, const float size);

		/**********************************************************************//**
			@brief			隣の部屋へのルートを検索する
			@param[in]		transform					敵の位置情報
			@param[out]		route						検索したルートを格納する配列
			@return			ルート検索に成功したらtrue、失敗したらfalse
		*//***********************************************************************/
		bool GetRouteToNextRoom(MRTransform& transform, std::vector<MRTransform>& route);

		/**********************************************************************//**
			@brief			自機へのルートを検索する
			@param[in]		transform					敵の位置情報
			@param[out]		route						検索したルートを格納する配列
			@return			ルート検索に成功したらtrue、失敗したらfalse
		*//***********************************************************************/
		bool GetRouteToPlayer(MRTransform& transform, std::vector<MRTransform>& route);

		/**********************************************************************//**
			@brief			自機との距離を計算する
			@param[in]		transform					動体の位置情報
			@return			動体と自機の距離
		*//***********************************************************************/
		float GetDistancePlayer(MRTransform& transform) const
		{
			return std::sqrtf(m_pPlayerTransform->GetDistance2(transform));
		}

	private:
		/**********************************************************************//**
			@class		ROOM_NODE
			@brief		マップ中の部屋を表す構造体
		*//***********************************************************************/
		struct ROOM_NODE
		{
			ROOM_NODE(int topX, int topY, int bottomX, int bottomY, int usedFor) :
				topX(topX), topY(topY), bottomX(bottomX), bottomY(bottomY), usedFor(usedFor)
			{}
			int topX;										//!< 左上のX座標
			int topY;										//!< 左上のY座標
			int bottomX;									//!< 右下のX座標
			int bottomY;									//!< 右下のY座標

			int usedFor;									//!< 部屋の使い道(0:無し 1:部屋 2:交差点)
		};

		/**********************************************************************//**
			@class		ROOM_INDEX
			@brief		部屋の番号を表す構造体
		*//***********************************************************************/
		struct ROOM_INDEX
		{
			ROOM_INDEX(int x, int y, int index) :x(x), y(y), index(index)
			{}

			int x;											//!< X座標
			int y;											//!< Y座標
			int index;										//!< 部屋番号
		};

		/**********************************************************************//**
			@brief			マップデータから表示に使うデータに変換する
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _ConvertGraphFromMap();

		/**********************************************************************//**
			@brief			マップデータを部屋割りする
			@param			なし
			@return			なし
		*//***********************************************************************/
		void _DivideRooms();

		/**********************************************************************//**
			@brief			プレイヤーの初期位置を決定する
			@param			index				部屋番号
			@return			なし
		*//***********************************************************************/
		void _SetStartPosition(const size_t index);

		/**********************************************************************//**
			@brief			階段の位置を決定する
			@param			index				部屋番号
			@return			なし
		*//***********************************************************************/
		void _SetGoalPosition(const size_t index);

		/**********************************************************************//**
			@brief			宝箱を設置する
			@param[in]		staticList					固定オブジェクトのリスト
			@return			なし
		*//***********************************************************************/
		void _SpawnTreasureBox(MRStaticObjectManager& staticList);

		/**********************************************************************//**
			@brief			敵のスポナーを設置する
			@param[in]		enemyManager				敵の管理者
			@return			なし
		*//***********************************************************************/
		void _CreateEnemySpawner(MREnemyManager& enemyManager);

		/**********************************************************************//**
			@brief			壁と位置速度情報の当たり判定
			@param			transform				位置速度情報
			@param[in]		size					物体のサイズ
			@param[in]		chipX					マップチップのX座標
			@param[in]		chipY					マップチップのY座標
			@param[in]		chipID					該当チップのID
			@return			当たっていたらチップID
		*//***********************************************************************/
		int _HitWall(MRTransform &transform, const float size, float chipX, float chipY, int chipID);
		
		/**********************************************************************//**
			@brief			ルートを検索する
			@param[in]		startX					始点のX位置
			@param[in]		startY					始点のY位置
			@param[in]		goalX					終点のX位置
			@param[in]		goalY					終点のY位置
			@param[out]		route					検索したルートを格納する配列
		*//***********************************************************************/
		void _FindRoute(const int startX, const int startY, const int goalX, const int goalY, std::vector<MRTransform>& route);

		int m_width;										//!< マップの横幅
		int m_height;										//!< マップの高さ

		MRTransform* m_pPlayerTransform;					//!< プレイヤーの位置速度情報
		int m_startX;										//!< プレイヤーの初期X座標
		int m_startY;										//!< プレイヤーの初期Y座標
		int m_goalX;										//!< 階段のX座標
		int m_goalY;										//!< 階段のY座標

		std::vector<std::vector<int>> m_mapData;			//!< マップデータ(壁=1, 床=0)
		std::vector<std::vector<int>> m_graphicData;		//!< 表示に使う方向とか入ってる奴
		std::vector<ROOM_NODE> m_roomList;					//!< 部屋リスト
		std::vector<ROOM_NODE> m_pathList;					//!< 通路リスト
		std::vector<ROOM_NODE> m_regionList;				//!< 領域リスト
		std::vector<std::set<int>> m_globalConnect;			//!< 接続状況

		float m_chipSize;									//!< マップチップの一辺の長さ

		mugen_engine::MEImage* m_mapchipImg;				//!< マップチップの画像
		mugen_engine::MEImage* m_minimapImg;				//!< ミニマップの画像
		mugen_engine::MEFontData* m_font;					//!< フォントデータ

		magica_rogue::MRRandom m_random;					//!< 乱数生成器

		std::vector<ROOM_INDEX> m_roomIndex;				//!< 部屋番号
	};
}

#endif//__MagicaRogue_MapData__