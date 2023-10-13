//! @file Random.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Random__
#define __MagicaRogue_Random__

#include <random>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRRandom
		@brief		乱数を扱うクラス
	*//***********************************************************************/
	class MRRandom
	{
	public:
		//! コンストラクタ
		MRRandom(uint32_t seed);
		//! 最小値と最大値を指定して乱数を取得
		uint32_t GetRanged(uint32_t minimum, uint32_t maximum);
	private:
		std::mt19937 m_engine;					//!< 乱数を生成するデバイス(メルセンヌツイスタ)
	};
}

#endif//__MagicaRogue_Random__