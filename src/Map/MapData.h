//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include "../Engine/Graphic/GraphicFontData.h"
#include "../util/Random.h"
#include <vector>
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMapData
		@brief		マップデータを扱うクラス
	*//***********************************************************************/
	class MRMapData
	{
	public:
		//! コンストラクタ
		MRMapData(const int width, const int height, uint32_t seed);
		//! マップを描画
		void Render(const int cameraX, const int cameraY) const;
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

		//! マップデータから表示に使うデータに変換する
		void _ConvertGraphFromMap();
		//! マップを部屋割りする
		void _DivideRooms();

		const int m_width;									//!< マップの横幅
		const int m_height;									//!< マップの高さ

		std::vector<std::vector<int>> m_mapData;			//!< マップデータ(壁=1, 床=0)
		std::vector<std::vector<int>> m_graphicData;		//!< 表示に使う方向とか入ってる奴

		mugen_engine::MEImage* m_mapchipImg;				//!< マップチップの画像
		mugen_engine::MEFontData* m_font;					//!< フォントデータ

		magica_rogue::MRRandom m_random;					//!< 乱数生成器

		std::vector<ROOM_INDEX> m_roomIndex;				//!< 部屋番号
	};
}

#endif//__MagicaRogue_MapData__