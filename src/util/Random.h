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
		//! 乱数を取得
		uint32_t Get();
		//! 最小値と最大値を指定して乱数を取得
		int GetRanged(int minimum, int maximum);
		//! デバイスを返す
		std::mt19937& GetDevice(){
			return m_engine;
		}
		//! シード値を設定する
		void SetSeed(uint32_t seed) {
			m_engine.seed(seed);
		}
	private:
		std::mt19937 m_engine;					//!< 乱数を生成するデバイス(メルセンヌツイスタ)
	};
}

#endif//__MagicaRogue_Random__