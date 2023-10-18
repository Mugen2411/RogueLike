//! @file SceneInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneInterface__
#define __MagicaRogue_SceneInterface__

#include "SceneManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneInterface
		@brief		シーンの要件を表すインターフェース
	*//***********************************************************************/
	class MRSceneInterface
	{
	public:
		//! コンストラクタ
		MRSceneInterface(MRSceneManager* sceneManager):m_pSceneManager(sceneManager)
		{}
		//! デストラクタ
		virtual ~MRSceneInterface(){}
		//! 更新
		virtual void Update() = 0;
		//! 描画
		virtual void Render() = 0;

	protected:
		MRSceneManager* m_pSceneManager;
	};
}

#endif//__MagicaRogue_SceneInterface__