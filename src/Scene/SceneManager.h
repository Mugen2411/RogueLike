//! @file SceneManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneManager__
#define __MagicaRogue_SceneManager__

#include <memory>
#include <stack>

namespace magica_rogue
{
	class MRSceneInterface;
	/**********************************************************************//**
		@class		MRSceneManager
		@brief		シーンの要件を表すインターフェース
	*//***********************************************************************/
	class MRSceneManager
	{
	public:
		//! コンストラクタ
		MRSceneManager();
		//! デストラクタ
		virtual ~MRSceneManager();
		//! シーンを1つ追加する
		virtual void Push(std::unique_ptr<MRSceneInterface>&& scene, bool isStackClear = false) = 0;
		//! シーンを1つ削除する
		virtual void Pop() = 0;
		//! シーンを更新する
		void Update();
		//! シーンを描画する
		void Render() const;
	protected:
		//! シーンを全部消す
		void _Reset();
		std::stack<std::unique_ptr<MRSceneInterface>> m_scenes;				//!< シーンを管理するスタック
	};
}

#endif//__MagicaRogue_SceneManager__