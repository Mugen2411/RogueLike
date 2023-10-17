//! @file Constants.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Constants__
#define __MagicaRogue_Constants__

namespace magica_rogue
{
	/**********************************************************************//**
		@namespace	constants
		@brief		ゲーム全体で使う定数
	*//***********************************************************************/
	namespace constants
	{
		/**********************************************************************//**
			@namespace	render_priority
			@brief		描画優先度を管理する定数群
		*//***********************************************************************/
		namespace render_priority
		{
			const float PLAYER = 0.0f;					//!< プレイヤー
			const float TREASURE_BOX = 1.0f;			//!< 宝箱
			const float MAP_WALL = 2.0f;				//!< マップの壁レイヤ
			const float MAP_FLOOR = 3.0f;				//!< マップの床レイヤ
			const float MINIMAP_BASE = -5.0f;			//!< ミニマップの基準
			const float MINIMAP_ROOM = -5.2f;			//!< ミニマップの部屋
			const float MINIMAP_PATH = -5.1f;			//!< ミニマップの通路
			const float MINIMAP_TREASUREBOX = -5.3f;	//!< ミニマップの宝箱
			const float MINIMAP_PLAYER = -5.8f;			//!< ミニマップのプレイヤー
			const float MINIMAP_DISCOVERED = -5.9f;		//!< ミニマップを隠すベール
		}

		/**********************************************************************//**
			@namespace	screen
			@brief		ゲーム画面に関わる定数
		*//***********************************************************************/
		namespace screen
		{
			const int left_margin = 128;				//!< UIで潰れる左部分の横幅
			const int width = (640 - left_margin);		//!< 残りの画面の横幅
			const int height = 360;						//!< 画面の高さ
		}
	}
}

#endif//__MagicaRogue_Constants__