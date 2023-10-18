//! @file Random.cpp
//! @note Copyright (c) Mugen_GameLab

#include "Random.h"
#include <cassert>

namespace magica_rogue
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		seed				�V�[�h�l
		@return			�Ȃ�
	*//***********************************************************************/
	MRRandom::MRRandom(uint32_t seed): m_engine(seed)
	{}

	/**********************************************************************//**
		@brief			�������擾
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	uint32_t MRRandom::Get()
	{
		return m_engine();
	}

	/**********************************************************************//**
		@brief			�ŏ��l�ƍő�l���w�肵�ė������擾
		@param[in]		minimum				�ŏ��l
		@param[in]		maximum				�ő�l
		@return			�Ȃ�
	*//***********************************************************************/
	uint32_t MRRandom::GetRanged(uint32_t minimum, uint32_t maximum)
	{
		assert(minimum <= maximum);
		uint32_t range = maximum - minimum + 1;
		return minimum + m_engine() % range;
	}
}