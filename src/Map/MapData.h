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
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MRMapData();
		
		/**********************************************************************//**
			@brief			�}�b�v�𐶐�����
			@param[in]		width				�}�b�v�̉���
			@param[in]		height				�}�b�v�̍���
			@param[in]		seed				�V�[�h�l
			@param[in]		staticList			�Î~�I�u�W�F�N�g�̊Ǘ���
			@param[in]		enemyManager		�G�̊Ǘ���
			@return			�Ȃ�
		*//***********************************************************************/
		void Construct(const int width, const int height, uint32_t seed, MRStaticObjectManager& staticList, MREnemyManager& enemyManager);

		/**********************************************************************//**
			@brief			�}�b�v���X�V����
			@param[in]		playerTransform			�v���C���[�̈ʒu
			@return			�Ȃ�
		*//***********************************************************************/
		void Update(const MRTransform& playerTransform);

		/**********************************************************************//**
			@brief			�}�b�v��`�悷��
			@param[in]		camera				�J����
			@return			�Ȃ�
		*//***********************************************************************/
		void Render(const MRCamera& camera) const;

		/**********************************************************************//**
			@brief			�~�j�}�b�v��`�悷��
			@param[in]		playerTransform			�v���C���[�̈ʒu
			@param[in]		staticList				�Î~�I�u�W�F�N�g�̊Ǘ���
			@return			�Ȃ�
		*//***********************************************************************/
		void RenderMiniMap(MRTransform& playerTransform, MRStaticObjectManager& staticList)const;

		/**********************************************************************//**
			@brief			�v���C���[�̏����ʒu��ݒ�
			@param[out]		playerTransform			�v���C���[�̈ʒu
			@return			�Ȃ�
		*//***********************************************************************/
		void SetPlayerPosition(MRTransform& playerTransform) {
			playerTransform.SetPosition(m_startX * 32.0f + 16.0f, m_startY * 32.0f + 16.0f);
			m_pPlayerTransform = &playerTransform;
		}

		/**********************************************************************//**
			@brief			�ǂƃv���C���[�̏Փ˂���������
			@param[in]		transform			�v���C���[�̈ʒu���x���
			@param[in]		size				�v���C���[�̈�ӂ̒���
			@param			eventQueue			�C�x���g�L���[
			@return			�Ȃ�
		*//***********************************************************************/
		void HitWallWithPlayer(MRTransform& transform, const float size, MREventQueue& eventQueue);
		
		/**********************************************************************//**
			@brief			�ǂƓG�̏Փ˂���������
			@param[in]		transform			�G�̈ʒu���x���
			@param[in]		size				�G�̈�ӂ̒���
			@return			�Ȃ�
		*//***********************************************************************/
		void HitWallWithEnemy(MRTransform& transform, const float size);

		/**********************************************************************//**
			@brief			�ׂ̕����ւ̃��[�g����������
			@param[in]		transform					�G�̈ʒu���
			@param[out]		route						�����������[�g���i�[����z��
			@return			���[�g�����ɐ���������true�A���s������false
		*//***********************************************************************/
		bool GetRouteToNextRoom(MRTransform& transform, std::vector<MRTransform>& route);

		/**********************************************************************//**
			@brief			���@�ւ̃��[�g����������
			@param[in]		transform					�G�̈ʒu���
			@param[out]		route						�����������[�g���i�[����z��
			@return			���[�g�����ɐ���������true�A���s������false
		*//***********************************************************************/
		bool GetRouteToPlayer(MRTransform& transform, std::vector<MRTransform>& route);

		/**********************************************************************//**
			@brief			���@�Ƃ̋������v�Z����
			@param[in]		transform					���̂̈ʒu���
			@return			���̂Ǝ��@�̋���
		*//***********************************************************************/
		float GetDistancePlayer(MRTransform& transform) const
		{
			return std::sqrtf(m_pPlayerTransform->GetDistance2(transform));
		}

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

		/**********************************************************************//**
			@brief			�}�b�v�f�[�^����\���Ɏg���f�[�^�ɕϊ�����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _ConvertGraphFromMap();

		/**********************************************************************//**
			@brief			�}�b�v�f�[�^�𕔉����肷��
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _DivideRooms();

		/**********************************************************************//**
			@brief			�v���C���[�̏����ʒu�����肷��
			@param			index				�����ԍ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _SetStartPosition(const size_t index);

		/**********************************************************************//**
			@brief			�K�i�̈ʒu�����肷��
			@param			index				�����ԍ�
			@return			�Ȃ�
		*//***********************************************************************/
		void _SetGoalPosition(const size_t index);

		/**********************************************************************//**
			@brief			�󔠂�ݒu����
			@param[in]		staticList					�Œ�I�u�W�F�N�g�̃��X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void _SpawnTreasureBox(MRStaticObjectManager& staticList);

		/**********************************************************************//**
			@brief			�G�̃X�|�i�[��ݒu����
			@param[in]		enemyManager				�G�̊Ǘ���
			@return			�Ȃ�
		*//***********************************************************************/
		void _CreateEnemySpawner(MREnemyManager& enemyManager);

		/**********************************************************************//**
			@brief			�ǂƈʒu���x���̓����蔻��
			@param			transform				�ʒu���x���
			@param[in]		size					���̂̃T�C�Y
			@param[in]		chipX					�}�b�v�`�b�v��X���W
			@param[in]		chipY					�}�b�v�`�b�v��Y���W
			@param[in]		chipID					�Y���`�b�v��ID
			@return			�������Ă�����`�b�vID
		*//***********************************************************************/
		int _HitWall(MRTransform &transform, const float size, float chipX, float chipY, int chipID);
		
		/**********************************************************************//**
			@brief			���[�g����������
			@param[in]		startX					�n�_��X�ʒu
			@param[in]		startY					�n�_��Y�ʒu
			@param[in]		goalX					�I�_��X�ʒu
			@param[in]		goalY					�I�_��Y�ʒu
			@param[out]		route					�����������[�g���i�[����z��
		*//***********************************************************************/
		void _FindRoute(const int startX, const int startY, const int goalX, const int goalY, std::vector<MRTransform>& route);

		int m_width;										//!< �}�b�v�̉���
		int m_height;										//!< �}�b�v�̍���

		MRTransform* m_pPlayerTransform;					//!< �v���C���[�̈ʒu���x���
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