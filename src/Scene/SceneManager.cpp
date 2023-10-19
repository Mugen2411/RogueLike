//! @file SceneManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "SceneManager.h"
#include "SceneInterface.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MRSceneManager::MRSceneManager()
	{}

	/**********************************************************************//**
		@brief			�f�X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MRSceneManager::~MRSceneManager()
	{}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneManager::Update()
	{
		if (!m_scenes.empty())
		{
			m_scenes.front()->Update();
		}
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneManager::Render() const
	{
		for (auto& s : m_scenes)
		{
			s->Render();
		}
	}

	/**********************************************************************//**
		@brief			�V�[����S�č폜����
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneManager::_Reset()
	{
		m_scenes.clear();
	}
}