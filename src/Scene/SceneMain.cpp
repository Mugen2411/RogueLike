//! @file SceneMain.cpp
//! @note Copyright (c) Mugen_GameLab

#include "SceneMain.h"
#include "../Menu/MenuNextFloor.h"
#include "../Mover/Enemy/EnemyFactory.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			sceneManager				�V�[���̊Ǘ���
		@return			�Ȃ�
	*//***********************************************************************/
	MRSceneMain::MRSceneMain(MRSceneManager* sceneManager) :m_floor(0), MRSceneInterface(sceneManager), MRMenuManager(m_eventQueue),
		m_camera(0,0), m_mapData(), 
		m_player(MRPlayer::PLAYER_ID::KOMUK, m_mapData.GetStartX(), m_mapData.GetStartY(), m_camera)
	{
		MREnemyFactory::GetIns().Initialize(m_camera, m_mapData);
		_GenerateMap();
	}

	/**********************************************************************//**
		@brief			�X�V
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneMain::Update()
	{
		MREventQueue::eventData ev = {};
		while (1)
		{
			ev = m_eventQueue.GetTop();
			if (ev.evnetId == MREventQueue::EVENT_ID::NONE) break;
			m_eventQueue.Pop();
			if (ev.evnetId == MREventQueue::EVENT_ID::SELECT_GOTO_NEXT_FLOOR)
			{
				Push(std::make_unique<MRMenuNextFloor>(m_eventQueue));
			}
			else if (ev.evnetId == MREventQueue::EVENT_ID::GOTO_NEXT_FLOOR)
			{
				m_eventQueue.Reset();
				++m_floor;
				_GenerateMap();
				continue;
			}
		}
		if (MRMenuManager::Update()) return;

		m_enemyManager.Update();
		m_player.Update();
		m_mapData.HitWithWall(m_player.GetTransform(), m_player.GetSize(), m_eventQueue);
		m_mapData.Update(m_player.GetTransform());
		m_player.Move();

	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneMain::Render()
	{
		m_mapData.Render(m_camera);
		m_mapData.RenderMiniMap(m_player.GetTransform(), m_staticObjectManager);
		m_staticObjectManager.Render(m_camera);
		m_player.Render();
		m_enemyManager.Render();
		MRMenuManager::Render();
	}

	/**********************************************************************//**
		@brief			�}�b�v�𐶐�����
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRSceneMain::_GenerateMap()
	{
		m_staticObjectManager.Reset();
		m_mapData.Construct(min(64+(m_floor/ 2), 256), min(64 + (m_floor / 2), 256), m_floor, m_staticObjectManager, m_enemyManager);
		m_player.GetTransform().SetPosition(m_mapData.GetStartX(), m_mapData.GetStartY());
	}
}