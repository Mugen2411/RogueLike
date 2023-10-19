//! @file SceneManager.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneManager__
#define __MagicaRogue_SceneManager__

#include <memory>
#include <list>

namespace magica_rogue
{
	class MRSceneInterface;
	/**********************************************************************//**
		@class		MRSceneParameter
		@brief		シーンが変更されるときに渡すパラメータを設定
	*//***********************************************************************/
	class MRSceneParameter
	{};

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
		virtual void Push(int sceneId, bool isStackClear = false) = 0;
		//! シーンを1つ削除する
		virtual void Pop() = 0;
		//! シーンを更新する
		void Update();
		//! シーンを描画する
		void Render() const;
	protected:
		//! シーンを全部消す
		void _Reset();
		std::list<std::unique_ptr<MRSceneInterface>> m_scenes;				//!< シーンを管理するスタック
	};
}

#endif//__MagicaRogue_SceneManager__