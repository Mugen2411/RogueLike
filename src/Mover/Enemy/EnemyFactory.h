//! @file EnemyFactory.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_EnemyFactory__
#define __MagicaRogue_EnemyFactory__

#include <memory>
#include <string>
#include "EnemyInterface.h"
#include "../../Map/MapData.h"
#include "../../Util/Constants.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MREnemyFactory
		@brief		�G�����ۂɐ�������N���X
	*//***********************************************************************/
	class MREnemyFactory
	{
	public:
		//! �C���X�^���X�̎擾
		static MREnemyFactory& GetIns();
		//! ������
		void Initialize(MRCamera& camera, MRMapData& mapdata);
		//! ����
		MREnemyInterface* Create(std::string name,
			const float x, const float y, const constants::MRAttribute attribute);
	private:
		//! �R���X�g���N�^
		MREnemyFactory();

		MRCamera* m_pCamera;				//!< �J����
		MRMapData* m_pMapdata;				//!< �}�b�v�f�[�^
		MRRandom m_random;					//!< ����������
	};
}

#endif//__MagicaRogue_EnemyFactory__