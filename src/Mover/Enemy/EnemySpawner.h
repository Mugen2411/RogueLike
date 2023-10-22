//! @file EnemySpawner.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemySpawner__
#define __MagicaRogue_EnemySpawner__

#include <vector>
#include <string>
#include "../../Util/Constants.h"
#include "../../Util/Random.h"

namespace magica_rogue
{
	class MREnemyManager;
	/**********************************************************************//**
		@class		MREnemySpawner
		@brief		�G�̃X�|�i�[�N���X
	*//***********************************************************************/
	class MREnemySpawner
	{
	public:
		//! �R���X�g���N�^
		MREnemySpawner(const int topX, const int topY, const int bottomX, const int bottomY, const int cycle, uint32_t seed)
			:m_cycle(cycle), m_cnt(0), m_topX(topX), m_topY(topY), m_bottomX(bottomX), m_bottomY(bottomY), m_random(seed)
		{
			m_cnt = m_random.GetRanged(0, m_cycle);
		}
		//! �X�V
		void Update(MREnemyManager& enemyManager);
		//! �G�f�[�^��ǉ�����
		void Push(std::string name, constants::MRAttribute attribute, int count);
	private:
		/**********************************************************************//**
			@struct		EnemyData
			@brief		�G�̏����ɕK�v�ȃf�[�^
		*//***********************************************************************/
		struct EnemyData
		{
			std::string name;						//!< ��������G�̖��O
			constants::MRAttribute attribute;		//!< �������鑮��
			int count;								//!< �������鐔
		};

		std::vector<EnemyData> m_enemyDataList;		//!< ��������ׂ��G�̃��X�g
		int m_cycle;								//!< �G�������������
		int m_cnt;									//!< �o�ߎ���(�t���[��)
		int m_topX;									//!< �����X���W
		int m_topY;									//!< �����Y���W
		int m_bottomX;								//!< �E����X���W
		int m_bottomY;								//!< �E����Y���W
		MRRandom m_random;							//!< ����������
	};
}

#endif//__MagicaRogue_EnemySpawner__