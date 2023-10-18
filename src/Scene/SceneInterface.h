//! @file SceneInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneInterface__
#define __MagicaRogue_SceneInterface__

#include "SceneManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneInterface
		@brief		�V�[���̗v����\���C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRSceneInterface
	{
	public:
		//! �R���X�g���N�^
		MRSceneInterface(MRSceneManager* sceneManager):m_pSceneManager(sceneManager)
		{}
		//! �f�X�g���N�^
		virtual ~MRSceneInterface(){}
		//! �X�V
		virtual void Update() = 0;
		//! �`��
		virtual void Render() = 0;

	protected:
		MRSceneManager* m_pSceneManager;
	};
}

#endif//__MagicaRogue_SceneInterface__