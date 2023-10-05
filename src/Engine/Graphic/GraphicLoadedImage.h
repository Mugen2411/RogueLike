//! @file GraphicLoadedImage.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicLoadedImage__
#define __MugenEngine_GraphicLoadedImage__

#include <cstdint>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicLoadedImage
		@brief		�ǂݍ��ݍς݉摜�������N���X
	*//***********************************************************************/
	class MEGraphicLoadedImage
	{
	public:
		//! �R���X�g���N�^
		MEGraphicLoadedImage();
		//! �R���X�g���N�^
		MEGraphicLoadedImage(uint32_t index, size_t width, size_t height);
	private:
		uint32_t m_index;										//!< �ǂݍ��݉摜�����Ԗڂ�
		size_t m_width;											//!< �摜�̉���
		size_t m_height;											//!< �摜�̍���
		size_t m_xDivideNum;										//!< �������̕�����
		size_t m_yDivideNum;										//!< �c�����̕�����
	};
}

#endif//__MugenEngine_GraphicLoadedImage__