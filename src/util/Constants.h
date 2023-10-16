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
			const float player = 0.0f;					//!< �v���C���[
			const float map_wall = 2.0f;				//!< �}�b�v�̕ǃ��C��
			const float map_floor = 3.0f;				//!< �}�b�v�̏����C��
			const float minimap_base = -5.0f;			//!< �~�j�}�b�v�̊
			const float minimap_room = -5.1f;			//!< �~�j�}�b�v�̕���
			const float minimap_path = -5.2f;			//!< �~�j�}�b�v�̒ʘH
			const float minimap_player = -5.3f;			//!< �~�j�}�b�v�̃v���C���[
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
	}
}

#endif//__MagicaRogue_Constants__