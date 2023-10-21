//! @file EnemyFactory.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyFactory.h"
#include "Slime/Slime.h"
#include "../../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�C���X�^���X�̎擾
		@param			�Ȃ�
		@return			�C���X�^���X
	*//***********************************************************************/
	MREnemyFactory& MREnemyFactory::GetIns()
	{
		static MREnemyFactory instance;
		return instance;
	}

	/**********************************************************************//**
		@brief			������
		@param			camera				�J����
		@param			mapdata				�}�b�v�f�[�^
		@return			�Ȃ�
	*//***********************************************************************/
	void MREnemyFactory::Initialize(MRCamera& camera, MRMapData& mapdata)
	{
		m_pCamera = &camera;
		m_pMapdata = &mapdata;
	}

	/**********************************************************************//**
		@brief			����
		@param[in]		name				�G�̖��O
		@param[in]		x					X���W
		@param[in]		y					Y���W
		@param[in]		attribute			����
		@return			�Ȃ�
	*//***********************************************************************/
	MREnemyInterface* MREnemyFactory::Create(std::string name,
		const float x, const float y, const constants::MRAttribute attribute)
	{
		if (name == "slime")
		{
			return new MRSlime(x, y, attribute, m_pCamera, m_pMapdata);
		}
		return nullptr;
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
		@detail			�G�̉摜�̓ǂݍ��݂͂����ł��܂�
	*//***********************************************************************/
	MREnemyFactory::MREnemyFactory(): m_pCamera(nullptr), m_pMapdata(nullptr)
	{
		mugen_engine::MECore::GetIns().LoadDivGraph("enemy_slime", L"media/graphic/enemy/slime.png", 10, 13);
	}
}