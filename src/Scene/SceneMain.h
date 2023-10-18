//! @file SceneMain.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneMain__
#define __MagicaRogue_SceneMain__

#include "SceneInterface.h"
#include "SceneManager.h"

#include "../Mover/Player/Player.h"
#include "../Map/MapData.h"
#include "../Static/StaticObjectManager.h"
#include "../Util/Camera.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneMain
		@brief		�Q�[���̃��C���V�[��
	*//***********************************************************************/
	class MRSceneMain :public MRSceneInterface
	{
	public:
		//! �R���X�g���N�^
		MRSceneMain(MRSceneManager* sceneManager);
		//! �X�V
		void Update();
		//! �`��
		void Render();
	private:
		//! mappuwoseiseisuru
		void _GenerateMap();

		int m_floor;												//!< gennzainokaisou
		MRCamera m_camera;										//!< �J����
		MRStaticObjectManager m_staticObjectManager;			//!< �Î~�I�u�W�F�N�g�̊Ǘ���
		MRMapData m_mapData;									//!< �}�b�v
		MRPlayer m_player;										//!< �v���C���[
	};
}

#endif//__MagicaRogue_SceneMain__