//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicStruct__
#define __MugenEngine_GraphicStruct__

#include <DirectXMath.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@struct		VERTEX_DATA
		@brief		頂点単位のデータ群
	*//***********************************************************************/
	struct VERTEX_DATA
	{
		DirectX::XMFLOAT3 pos;									//!< 頂点の座標
		DirectX::XMFLOAT2 uv;									//!< テクスチャのUV座標
	};
}

#endif//__MugenEngine_GraphicStruct__