#include "SceneMain.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			sceneManager				シーンの管理者
		@return			なし
	*//***********************************************************************/
	MRSceneMain::MRSceneMain(MRSceneManager* sceneManager) :m_floor(0), MRSceneInterface(sceneManager), 
		m_camera(0,0), m_mapData(), 
		m_player(MRPlayer::PLAYER_ID::KOMUK, m_mapData.GetStartX(), m_mapData.GetStartY(), m_camera)
	{
		_GenerateMap();
	}

	/**********************************************************************//**
		@brief			更新
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRSceneMain::Update()
	{
		m_player.Update();
		m_mapData.HitWithWall(m_player.GetTransform(), m_player.GetSize());
		m_mapData.Update(m_player.GetTransform());
		m_player.Move();
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRSceneMain::Render()
	{
		m_mapData.Render(m_camera);
		m_mapData.RenderMiniMap(m_player.GetTransform(), m_staticObjectManager);
		m_staticObjectManager.Render(m_camera);
		m_player.Render();
	}
	void MRSceneMain::_GenerateMap()
	{
		m_staticObjectManager.Reset();
		m_mapData.Construct(64, 64, m_floor, m_staticObjectManager);
		m_player.GetTransform().SetPosition(m_mapData.GetStartX(), m_mapData.GetStartY());
	}
}