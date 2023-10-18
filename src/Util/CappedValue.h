//! @file CappedValue.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_CappedValue__
#define __MagicaRogue_CappedValue__

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRCappedValue
		@brief		�ő�l�ƍŏ��l�����܂��Ă��鐔�l�������N���X
	*//***********************************************************************/
	class MRCappedValue
	{
	public:
		//! �R���X�g���N�^
		MRCappedValue(const float initialValue, const float minimumValue, const float maximumValue);
		//! �l���擾
		float GetValue() const;
		//! ���Z
		float Add(const float value);
		//! �ŏ��l���ǂ���
		bool isMinimum() const;
		//! �ő�l���ǂ���
		bool isMaximum() const;
		//! �������擾
		float GetRatio() const;
	private:
		float m_value;							//!< ���ݒl
		float m_minimum;						//!< �ŏ��l
		float m_maximum;						//!< �ő�l
	};
}

#endif//__MagicaRogue_CappedValue__