//! @file EnemySpawner.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemySpawner__
#define __MagicaRogue_EnemySpawner__

#include <vector>
#include <string>
#include "../../Util/Constants.h"

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
		MREnemySpawner(const float x, const float y, const int cycle)
			:m_cycle(cycle), m_cnt(0), m_x(x), m_y(y)
		{
			m_enemyDataList.push_back(EnemyData{ "slime", constants::MRAttribute::ABYSS, 1 });
		}
		//! �X�V
		void Update(MREnemyManager& enemyManager);
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
		float m_x;									//!< X���W
		float m_y;									//!< Y���W
	};
}

#endif//__MagicaRogue_EnemySpawner__