#include "Core.h"
//! @file Core.cpp
//! @note Copyright (c) Mugen_GameLab

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			インスタンスの取得
		@param			なし
		@return			インスタンス
	*//***********************************************************************/
	MECore& MECore::GetIns() const
	{
		static MECore instance;
		return instance;
	}

	/**********************************************************************//**
		@brief			初期化
		@param[in]		window_width		ウィンドウ(描画範囲)の横幅
		@param[in]		window_height		ウィンドウ(描画範囲)の縦幅
		@return			インスタンス
	*//***********************************************************************/
	void MECore::Initialize(const int window_width, const int window_height)
	{
		graphicCore.Initialize(window_width, window_height);
	}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param			なし
		@return			なし
	*//***********************************************************************/
	MECore::MECore()
	{}
}
