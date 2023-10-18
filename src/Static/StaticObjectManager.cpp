//! @file StaticObjectManager.cpp
//! @note Copyright (c) Mugen_GameLab

#include "StaticObjectManager.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MRStaticObjectManager::MRStaticObjectManager()
	{}

	/**********************************************************************//**
		@brief			静止オブジェクトを登録する
		@param[in]		obj			対象のオブジェクト
		@return			なし
	*//***********************************************************************/
	void MRStaticObjectManager::Register(std::unique_ptr<MRStaticObjectInterface>&& obj)
	{
		m_objectList.push_back(std::move(obj));
	}

	/**********************************************************************//**
		@brief			全ての静止オブジェクトを解放する
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRStaticObjectManager::Reset()
	{
		m_objectList.clear();
	}

	/**********************************************************************//**
		@brief			位置情報をvectorで取得
		@param[out]		list			位置情報を格納するvector
		@return			なし
	*//***********************************************************************/
	void MRStaticObjectManager::GetTransforms(std::vector<MRTransform>& list)
	{
		for (auto& obj : m_objectList)
		{
			list.push_back(obj->GetTransform());
		}
	}

	/**********************************************************************//**
		@brief			描画
		@param			なし
		@return			なし
	*//***********************************************************************/
	void MRStaticObjectManager::Render(const MRCamera& camera) const
	{
		for (auto& obj : m_objectList)
		{
			obj->Render(camera);
		}
	}
}