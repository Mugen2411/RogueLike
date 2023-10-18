//! @file SceneMain.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneMain__
#define __MagicaRogue_SceneMain__

#include "SceneInterface.h"
#include "SceneManager.h"

#include "../Mover/Player/Player.h"
#include "../Map/MapData.h"
#include "../Static/StaticObjectManager.h"
#include "../Util/Camera.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneMain
		@brief		ゲームのメインシーン
	*//***********************************************************************/
	class MRSceneMain :public MRSceneInterface
	{
	public:
		//! コンストラクタ
		MRSceneMain(MRSceneManager* sceneManager);
		//! 更新
		void Update();
		//! 描画
		void Render();
	private:
		//! mappuwoseiseisuru
		void _GenerateMap();

		int m_floor;												//!< gennzainokaisou
		MRCamera m_camera;										//!< カメラ
		MRStaticObjectManager m_staticObjectManager;			//!< 静止オブジェクトの管理者
		MRMapData m_mapData;									//!< マップ
		MRPlayer m_player;										//!< プレイヤー
	};
}

#endif//__MagicaRogue_SceneMain__