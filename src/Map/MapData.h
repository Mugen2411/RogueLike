//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include <vector>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMapData
		@brief		�}�b�v�f�[�^�������N���X
	*//***********************************************************************/
	class MRMapData
	{
	public:
		MRMapData(const int width, const int height);
		void Render(const int cameraX, const int cameraY) const;
	private:
		void _ConvertGraphFromMap();						//!< �}�b�v�f�[�^����\���Ɏg���f�[�^�ɕϊ�����

		const int m_width;									//!< �}�b�v�̉���
		const int m_height;									//!< �}�b�v�̍���

		std::vector<std::vector<int>> m_mapData;			//!< �}�b�v�f�[�^(��=1, ��=0)
		std::vector<std::vector<int>> m_graphicData;		//!< �\���Ɏg�������Ƃ������Ă�z

		mugen_engine::MEImage* m_mapchipImg;				//!< �}�b�v�`�b�v�̉摜
	};
}

#endif//__MagicaRogue_MapData__