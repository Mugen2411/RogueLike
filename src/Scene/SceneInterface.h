//! @file SceneInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneInterface__
#define __MagicaRogue_SceneInterface__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneInterface
		@brief		シーンの要件を表すインターフェース
	*//***********************************************************************/
	class MRSceneInterface
	{
	public:
		//! デストラクタ
		virtual ~MRSceneInterface(){}
		//! 更新
		virtual void Update() = 0;
		//! 描画
		virtual void Render() const = 0;
	};
}

#endif//__MagicaRogue_SceneInterface__