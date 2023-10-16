//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include "../Engine/Graphic/GraphicFontData.h"
#include "../util/Camera.h"
#include "../util/Random.h"
#include "../util/Transform.h"
#include <vector>
#include <memory>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRMapData
		@brief		�}�b�v�f�[�^�������N���X
	*//***********************************************************************/
	class MRMapData
	{
	public:
		//! �R���X�g���N�^
		MRMapData(const int width, const int height, uint32_t seed);
		//! �}�b�v��`��
		void Render(const MRCamera& camera) const;
		//! �~�j�}�b�v��`��
		void RenderMiniMap(const MRTransform& playerTransform)const;
		//! �v���C���[�̏���X���W���擾
		float GetStartX() const {
			return m_startX * 32.0f + 16.0f;
		}
		//! �v���C���[�̏���Y���W���擾
		float GetStartY() const {
			return m_startY * 32.0f + 16.0f;
		}
		//! �ǂƕ��̂̏Փ˂���������
		void HitWithWall(MRTransform& transform, const float size);
	private:
		/**********************************************************************//**
			@class		ROOM_NODE
			@brief		�}�b�v���̕�����\���\����
		*//***********************************************************************/
		struct ROOM_NODE
		{
			ROOM_NODE(int topX, int topY, int bottomX, int bottomY, int usedFor) :
				topX(topX), topY(topY), bottomX(bottomX), bottomY(bottomY), usedFor(usedFor)
			{}
			int topX;										//!< �����X���W
			int topY;										//!< �����Y���W
			int bottomX;									//!< �E����X���W
			int bottomY;									//!< �E����Y���W
			
			int usedFor;									//!< �����̎g����(0:���� 1:���� 2:�����_)
		};

		/**********************************************************************//**
			@class		ROOM_INDEX
			@brief		�����̔ԍ���\���\����
		*//***********************************************************************/
		struct ROOM_INDEX
		{
			ROOM_INDEX(int x, int y, int index) :x(x), y(y), index(index) 
			{}

			int x;											//!< X���W
			int y;											//!< Y���W
			int index;										//!< �����ԍ�
		};

		//! �}�b�v�f�[�^����\���Ɏg���f�[�^�ɕϊ�����
		void _ConvertGraphFromMap();
		//! �}�b�v�𕔉����肷��
		void _DivideRooms();
		//! �v���C���[�̏����ʒu��ݒ肷��
		void _SetStartPosition(std::vector<ROOM_NODE>& rooms);

		const int m_width;									//!< �}�b�v�̉���
		const int m_height;									//!< �}�b�v�̍���

		int m_startX;										//!< �v���C���[�̏���X���W
		int m_startY;										//!< �v���C���[�̏���Y���W

		std::vector<std::vector<int>> m_mapData;			//!< �}�b�v�f�[�^(��=1, ��=0)
		std::vector<std::vector<int>> m_graphicData;		//!< �\���Ɏg�������Ƃ������Ă�z
		std::vector<ROOM_NODE> m_roomList;					//!< �������X�g
		std::vector<ROOM_NODE> m_pathList;					//!< �ʘH���X�g

		float m_chipSize;									//!< �}�b�v�`�b�v�̈�ӂ̒���

		mugen_engine::MEImage* m_mapchipImg;				//!< �}�b�v�`�b�v�̉摜
		mugen_engine::MEImage* m_minimapImg;				//!< �~�j�}�b�v�̉摜
		mugen_engine::MEFontData* m_font;					//!< �t�H���g�f�[�^

		magica_rogue::MRRandom m_random;					//!< ����������

		std::vector<ROOM_INDEX> m_roomIndex;				//!< �����ԍ�
	};
}

#endif//__MagicaRogue_MapData__