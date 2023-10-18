//! @file Random.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Random.h"
#include <cassert>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		seed				シード値
		@return			なし
	*//***********************************************************************/
	MRRandom::MRRandom(uint32_t seed): m_engine(seed)
	{}

	/**********************************************************************//**
		@brief			乱数を取得
		@param			なし
		@return			なし
	*//***********************************************************************/
	uint32_t MRRandom::Get()
	{
		return m_engine();
	}

	/**********************************************************************//**
		@brief			最小値と最大値を指定して乱数を取得
		@param[in]		minimum				最小値
		@param[in]		maximum				最大値
		@return			なし
	*//***********************************************************************/
	uint32_t MRRandom::GetRanged(uint32_t minimum, uint32_t maximum)
	{
		assert(minimum <= maximum);
		uint32_t range = maximum - minimum + 1;
		return minimum + m_engine() % range;
	}
}