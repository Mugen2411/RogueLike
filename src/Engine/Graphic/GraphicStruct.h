//! @file GraphicStruct.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicStruct__
#define __MugenEngine_GraphicStruct__

#include <DirectXMath.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@struct		VERTEX_DATA
		@brief		���_�P�ʂ̃f�[�^�Q
	*//***********************************************************************/
	struct VERTEX_DATA
	{
		DirectX::XMFLOAT3 pos;									//!< ���_�̍��W
		DirectX::XMFLOAT2 uv;									//!< �e�N�X�`����UV���W
	};
}

#endif//__MugenEngine_GraphicStruct__