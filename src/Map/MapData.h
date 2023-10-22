//! @file MapData.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_MapData__
#define __MagicaRogue_MapData__

#include "../Engine/Graphic/GraphicLoadedImage.h"
#include "../Engine/Graphic/GraphicFontData.h"
#include "../util/Camera.h"
#include "../util/Random.h"
#include "../util/Transform.h"
#include "../Static/StaticObjectInterface.h"
#include "../Static/TreasureBox.h"
#include "../Static/StaticObjectManager.h"
#include "../Mover/Enemy/EnemyManager.h"
#include <vector>
#include <memory>
#include <set>

namespace magica_rogue
{
	class MREventQueue;
	/**********************************************************************//**
		@class		MRMapData
		@brief		�}�b�v�f�[�^�������N���X
	*//***********************************************************************/
	class MRMapData
	{
	public:
		//! �R���X�g���N�^
		MRMapData();
		//! �}�b�v�𐶐�
		void Construct(const int width, const int height, uint32_t seed, MRStaticObjectManager& staticList, MREnemyManager& enemyManager);
		//! �}�b�v���X�V
		void Update(const MRTransform& playerTransform);
		//! �}�b�v��`��
		void Render(const MRCamera& camera) const;
		//! �~�j�}�b�v��`��
		void RenderMiniMap(MRTransform& playerTransform, MRStaticObjectManager& staticList)const;
		//! �v���C���[�̏���X���W���擾
		float GetStartX() const {
			return m_startX * 32.0f + 16.0f;
		}
		//! �v���C���[�̏���Y���W���擾
		float GetStartY() const {
			return m_startY * 32.0f + 16.0f;
		}
		//! �ǂƃv���C���[�̏Փ˂���������
		void HitWallWithPlayer(MRTransform& transform, const float size, MREventQueue& eventQueue);
		//! �ǂƓG�̏Փ˂���������
		void HitWallWithEnemy(MRTransform& transform, const float size);
		//! �ׂ̕����ւ̃��[�g���擾����
		bool GetRouteToNextRoom(MRTransform& transform, std::vector<MRTransform>& route);
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
		void _SetStartPosition(const size_t index);
		//! �K�i�̈ʒu��ݒ肷��
		void _SetGoalPosition(const size_t index);
		//! �󔠂�ݒu����
		void _SpawnTreasureBox(MRStaticObjectManager& staticList);
		//! �G�̃X�|�i�[��ݒu����
		void _CreateEnemySpawner(MREnemyManager& enemyManager);
		//! �ǂƈʒu���x���̓����蔻��
		int _HitWall(MRTransform &transform, const float size, float chipX, float chipY, int chipID);

		int m_width;									//!< �}�b�v�̉���
		int m_height;									//!< �}�b�v�̍���

		int m_startX;										//!< �v���C���[�̏���X���W
		int m_startY;										//!< �v���C���[�̏���Y���W
		int m_goalX;										//!< �K�i��X���W
		int m_goalY;										//!< �K�i��Y���W

		std::vector<std::vector<int>> m_mapData;			//!< �}�b�v�f�[�^(��=1, ��=0)
		std::vector<std::vector<int>> m_graphicData;		//!< �\���Ɏg�������Ƃ������Ă�z
		std::vector<ROOM_NODE> m_roomList;					//!< �������X�g
		std::vector<ROOM_NODE> m_pathList;					//!< �ʘH���X�g
		std::vector<ROOM_NODE> m_regionList;				//!< �̈惊�X�g
		std::vector<std::set<int>> m_globalConnect;			//!< �ڑ���

		float m_chipSize;									//!< �}�b�v�`�b�v�̈�ӂ̒���

		mugen_engine::MEImage* m_mapchipImg;				//!< �}�b�v�`�b�v�̉摜
		mugen_engine::MEImage* m_minimapImg;				//!< �~�j�}�b�v�̉摜
		mugen_engine::MEFontData* m_font;					//!< �t�H���g�f�[�^

		magica_rogue::MRRandom m_random;					//!< ����������

		std::vector<ROOM_INDEX> m_roomIndex;				//!< �����ԍ�
	};
}

#endif//__MagicaRogue_MapData__