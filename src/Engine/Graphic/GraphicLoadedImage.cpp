//! @file GraphicLoadedImage.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicLoadedImage.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param		�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage():
		m_index(0), m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1)
	{}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param[in]		index				�摜�ǂݍ��ݎ��̃C���f�b�N�X
		@param[in]		width				�摜�̉���
		@param[in]		height				�摜�̍���
		@return			�Ȃ�
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage(uint32_t index, size_t width, size_t height): 
		m_index(index), m_width(width), m_height(height), m_xDivideNum(1), m_yDivideNum(1)
	{}
}
