//! @file StaticObjectManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_StaticObjectManager__
#define __MagicaRogue_StaticObjectManager__

#include "StaticObjectInterface.h"
#include "../Util/Camera.h"
#include <list>
#include <vector>
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRStaticObjectManager
		@brief		静止オブジェクトを管理するクラス
	*//***********************************************************************/
	class MRStaticObjectManager
	{
	public:
		//! コンストラクタ
		MRStaticObjectManager();
		//! 管理対象に追加する
		void Register(std::unique_ptr<MRStaticObjectInterface>&& obj);
		//! 物体の位置情報をvectorで取得
		void GetTransforms(std::vector<MRTransform>& list);
		//! 描画
		void Render(const MRCamera& camera) const;
	private:
		std::list<std::unique_ptr<MRStaticObjectInterface>> m_objectList;			//!< オブジェクトのリスト
	};
}

#endif//__MagicaRogue_StaticObjectManager__