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

	/**********************************************************************//**
		@struct		CONSTANT_DATA
		@brief		定数バッファのデータ群
	*//***********************************************************************/
	struct CONSTANT_DATA
	{
		DirectX::XMMATRIX moveMatrix;							//!< 変形行列(並行移動)
		DirectX::XMMATRIX rotateMatrix;							//!< 変形行列(回転)
		DirectX::XMMATRIX scaleMatrix;							//!< 変形行列(拡大)
		DirectX::XMFLOAT4 brightness;							//!< 輝度調整
	private:
		DirectX::XMFLOAT4 dummy1;
		DirectX::XMFLOAT4 dummy2;
		DirectX::XMFLOAT4 dummy3;
	};
}

#endif//__MugenEngine_GraphicStruct__