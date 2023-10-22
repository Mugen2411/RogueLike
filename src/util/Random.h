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
		//! �������擾
		uint32_t Get();
		//! �ŏ��l�ƍő�l���w�肵�ė������擾
		int GetRanged(int minimum, int maximum);
		//! �f�o�C�X��Ԃ�
		std::mt19937& GetDevice(){
			return m_engine;
		}
		//! �V�[�h�l��ݒ肷��
		void SetSeed(uint32_t seed) {
			m_engine.seed(seed);
		}
	private:
		std::mt19937 m_engine;					//!< �����𐶐�����f�o�C�X(�����Z���k�c�C�X�^)
	};
}

#endif//__MagicaRogue_Random__