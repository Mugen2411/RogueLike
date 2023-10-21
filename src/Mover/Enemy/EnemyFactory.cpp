//! @file EnemyFactory.cpp
//! @note Copyright (c) Mugen_GameLab

#include "EnemyFactory.h"
#include "Slime/Slime.h"
#include "../../Engine/Core.h"

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			インスタンスの取得
		@param			なし
		@return			インスタンス
	*//***********************************************************************/
	MREnemyFactory& MREnemyFactory::GetIns()
	{
		static MREnemyFactory instance;
		return instance;
	}

	/**********************************************************************//**
		@brief			初期化
		@param			camera				カメラ
		@param			mapdata				マップデータ
		@return			なし
	*//***********************************************************************/
	void MREnemyFactory::Initialize(MRCamera& camera, MRMapData& mapdata)
	{
		m_pCamera = &camera;
		m_pMapdata = &mapdata;
	}

	/**********************************************************************//**
		@brief			生成
		@param[in]		name				敵の名前
		@param[in]		x					X座標
		@param[in]		y					Y座標
		@param[in]		attribute			属性
		@return			なし
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
		@brief			コンストラクタ
		@param			なし
		@return			なし
		@detail			敵の画像の読み込みはここでやります
	*//***********************************************************************/
	MREnemyFactory::MREnemyFactory(): m_pCamera(nullptr), m_pMapdata(nullptr)
	{
		mugen_engine::MECore::GetIns().LoadDivGraph("enemy_slime", L"media/graphic/enemy/slime.png", 10, 13);
	}
}