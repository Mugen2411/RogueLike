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
		@brief		�V�[�����ύX�����Ƃ��ɓn���p�����[�^��ݒ�
	*//***********************************************************************/
	class MRSceneParameter
	{};

	/**********************************************************************//**
		@class		MRSceneManager
		@brief		�V�[���̗v����\���C���^�[�t�F�[�X
	*//***********************************************************************/
	class MRSceneManager
	{
	public:
		//! �R���X�g���N�^
		MRSceneManager();
		//! �f�X�g���N�^
		virtual ~MRSceneManager();
		//! �V�[����1�ǉ�����
		virtual void Push(int sceneId, bool isStackClear = false) = 0;
		//! �V�[����1�폜����
		virtual void Pop() = 0;
		//! �V�[�����X�V����
		void Update();
		//! �V�[����`�悷��
		void Render() const;
	protected:
		//! �V�[����S������
		void _Reset();
		std::list<std::unique_ptr<MRSceneInterface>> m_scenes;				//!< �V�[�����Ǘ�����X�^�b�N
	};
}

#endif//__MagicaRogue_SceneManager__