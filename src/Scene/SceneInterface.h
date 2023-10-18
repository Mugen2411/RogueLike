//! @file SceneInterface.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_SceneInterface__
#define __MagicaRogue_SceneInterface__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRSceneInterface
		@brief		�V�[���̗v����\���C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRSceneInterface
	{
	public:
		//! �f�X�g���N�^
		virtual ~MRSceneInterface(){}
		//! �X�V
		virtual void Update() = 0;
		//! �`��
		virtual void Render() const = 0;
	};
}

#endif//__MagicaRogue_SceneInterface__