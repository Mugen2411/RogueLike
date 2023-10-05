//! @file GraphicLoadedImage.cpp
//! @note Copyright (c) Mugen_GameLab

#include "GraphicLoadedImage.h"

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			コンストラクタ
		@param		なし
		@return			なし
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage():
		m_index(0), m_width(0), m_height(0), m_xDivideNum(1), m_yDivideNum(1)
	{}

	/**********************************************************************//**
		@brief			コンストラクタ
		@param[in]		index				画像読み込み時のインデックス
		@param[in]		width				画像の横幅
		@param[in]		height				画像の高さ
		@return			なし
	*//***********************************************************************/
	MEGraphicLoadedImage::MEGraphicLoadedImage(uint32_t index, size_t width, size_t height): 
		m_index(index), m_width(width), m_height(height), m_xDivideNum(1), m_yDivideNum(1)
	{}
}
