//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include <vector>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMapData
		@brief		マップデータを扱うクラス
	*//***********************************************************************/
	class MRMapData
	{
	public:
		MRMapData(const int width, const int height);
		void Render(const int cameraX, const int cameraY) const;
	private:
		void _ConvertGraphFromMap();						//!< マップデータから表示に使うデータに変換する

		const int m_width;									//!< マップの横幅
		const int m_height;									//!< マップの高さ

		std::vector<std::vector<int>> m_mapData;			//!< マップデータ(壁=1, 床=0)
		std::vector<std::vector<int>> m_graphicData;		//!< 表示に使う方向とか入ってる奴

		mugen_engine::MEImage* m_mapchipImg;				//!< マップチップの画像
	};
}

#endif//__MagicaRogue_MapData__