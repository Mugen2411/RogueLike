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
			m_scenes.top()->Update();
		}
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneManager::Render() const
	{
		if (!m_scenes.empty())
		{
			m_scenes.top()->Render();
		}
	}

	/**********************************************************************//**
		@brief			�V�[����S�č폜����
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneManager::_Reset()
	{
		while (!m_scenes.empty())
		{
			m_scenes.pop();
		}
	}
}