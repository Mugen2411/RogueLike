//! @file GraphicLoadedImage.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicLoadedImage__
#define __MugenEngine_GraphicLoadedImage__

#include <cstdint>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicLoadedImage
		@brief		読み込み済み画像を扱うクラス
	*//***********************************************************************/
	class MEGraphicLoadedImage
	{
	public:
		//! コンストラクタ
		MEGraphicLoadedImage();
		//! コンストラクタ
		MEGraphicLoadedImage(uint32_t index, size_t width, size_t height);
	private:
		uint32_t m_index;										//!< 読み込み画像が何番目か
		size_t m_width;											//!< 画像の横幅
		size_t m_height;											//!< 画像の高さ
		size_t m_xDivideNum;										//!< 横方向の分割数
		size_t m_yDivideNum;										//!< 縦方向の分割数
	};
}

#endif//__MugenEngine_GraphicLoadedImage__