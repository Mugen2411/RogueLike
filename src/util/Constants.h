//! @file Constants.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Constants__
#define __MagicaRogue_Constants__

namespace magica_rogue
{
	/**********************************************************************//**
		@namespace	constants
		@brief		�Q�[���S�̂Ŏg���萔
	*//***********************************************************************/
	namespace constants
	{
		/**********************************************************************//**
			@namespace	render_priority
			@brief		�`��D��x���Ǘ�����萔�Q
		*//***********************************************************************/
		namespace render_priority
		{
			const float PLAYER = 0.0f;					//!< �v���C���[
			const float ENEMY = 0.5f;
			const float TREASURE_BOX = 1.0f;			//!< ��

			const float MAP_WALL = 2.0f;				//!< �}�b�v�̕ǃ��C��
			const float MAP_FLOOR = 3.0f;				//!< �}�b�v�̏����C��

			const float MINIMAP_BASE = -5.0f;			//!< �~�j�}�b�v�̊
			const float MINIMAP_ROOM = -5.2f;			//!< �~�j�}�b�v�̕���
			const float MINIMAP_PATH = -5.1f;			//!< �~�j�}�b�v�̒ʘH
			const float MINIMAP_TREASUREBOX = -5.3f;	//!< �~�j�}�b�v�̕�
			const float MINIMAP_PLAYER = -5.8f;			//!< �~�j�}�b�v�̃v���C���[
			const float MINIMAP_DISCOVERED = -5.9f;		//!< �~�j�}�b�v���B���x�[��

			const float UI_GUAGE_BASE = -6.0f;			//!< UI�Q�[�W�̃x�[�X
			const float UI_GUAGE_MAIN = -6.1f;			//!< UI�Q�[�W�̖{��
			const float UI_GUAGE_FRAME = -6.2f;			//!< UI�Q�[�W�̃t���[��
			const float UI_GUAGE_NUMBER = -6.3f;		//!< UI�Q�[�W�ɏd�˂�����l

			const float MENU1_BASE = -100.0f;			//!< ���j���[1���ڂ̊
			const float MENU1_TEXT = -101.0f;			//!< ���j���[1���ڂ̃e�L�X�g
		}

		/**********************************************************************//**
			@namespace	screen
			@brief		�Q�[����ʂɊւ��萔
		*//***********************************************************************/
		namespace screen
		{
			const int left_margin = 128;				//!< UI�Œׂ�鍶�����̉���
			const int width = (640 - left_margin);		//!< �c��̉�ʂ̉���
			const int height = 360;						//!< ��ʂ̍���
		}

		/**********************************************************************//**
			@enum		MRAttribute
			@brief		������\���萔
		*//***********************************************************************/
		enum class MRAttribute
		{
			NONE = 0, FIRE, AQUA, ICE, WIND, POISON, FLOWER, THUNDER, EARTH, GHOST, ABYSS, HOLY, PHANTOM
		};

		int operator*(MRAttribute lhs, int rhs);
	}
}

#endif//__MagicaRogue_Constants__