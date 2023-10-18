//! @file SceneManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "SceneManager.h"
#include "SceneInterface.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRSceneManager::MRSceneManager()
	{}

	/**********************************************************************//**
		@brief			デストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRSceneManager::~MRSceneManager()
	{}

	/**********************************************************************//**
		@brief			更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRSceneManager::Update()
	{
		if (!m_scenes.empty())
		{
			m_scenes.top()->Update();
		}
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRSceneManager::Render() const
	{
		if (!m_scenes.empty())
		{
			m_scenes.top()->Render();
		}
	}

	/**********************************************************************//**
		@brief			シーンを全て削除する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRSceneManager::_Reset()
	{
		while (!m_scenes.empty())
		{
			m_scenes.pop();
		}
	}
}