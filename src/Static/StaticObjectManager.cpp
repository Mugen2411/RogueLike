//! @file StaticObjectManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "StaticObjectManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MRStaticObjectManager::MRStaticObjectManager()
	{}

	/**********************************************************************//**
		@brief			�Î~�I�u�W�F�N�g��o�^����
		@param[in]		obj			�Ώۂ̃I�u�W�F�N�g
		@return			�Ȃ�
	*//***********************************************************************/
	void MRStaticObjectManager::Register(std::unique_ptr<MRStaticObjectInterface>&& obj)
	{
		m_objectList.push_back(std::move(obj));
	}

	/**********************************************************************//**
		@brief			�S�Ă̐Î~�I�u�W�F�N�g���������
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRStaticObjectManager::Reset()
	{
		m_objectList.clear();
	}

	/**********************************************************************//**
		@brief			�ʒu����vector�Ŏ擾
		@param[out]		list			�ʒu�����i�[����vector
		@return			�Ȃ�
	*//***********************************************************************/
	void MRStaticObjectManager::GetTransforms(std::vector<MRTransform>& list)
	{
		for (auto& obj : m_objectList)
		{
			list.push_back(obj->GetTransform());
		}
	}

	/**********************************************************************//**
		@brief			�`��
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	void MRStaticObjectManager::Render(const MRCamera& camera) const
	{
		for (auto& obj : m_objectList)
		{
			obj->Render(camera);
		}
	}
}