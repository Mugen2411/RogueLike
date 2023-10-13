//! @file Random.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_Random__
#define __MagicaRogue_Random__

#include <random>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRRandom
		@brief		�����������N���X
	*//***********************************************************************/
	class MRRandom
	{
	public:
		//! �R���X�g���N�^
		MRRandom(uint32_t seed);
		//! �ŏ��l�ƍő�l���w�肵�ė������擾
		uint32_t GetRanged(uint32_t minimum, uint32_t maximum);
	private:
		std::mt19937 m_engine;					//!< �����𐶐�����f�o�C�X(�����Z���k�c�C�X�^)
	};
}

#endif//__MagicaRogue_Random__