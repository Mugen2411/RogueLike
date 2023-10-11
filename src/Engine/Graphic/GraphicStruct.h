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

	/**********************************************************************//**
		@struct		CONSTANT_DATA
		@brief		�萔�o�b�t�@�̃f�[�^�Q
	*//***********************************************************************/
	struct CONSTANT_DATA
	{
		DirectX::XMMATRIX moveMatrix;							//!< �ό`�s��(���s�ړ�)
		DirectX::XMMATRIX rotateMatrix;							//!< �ό`�s��(��])
		DirectX::XMMATRIX scaleMatrix;							//!< �ό`�s��(�g��)
		DirectX::XMFLOAT4 brightness;							//!< �P�x����
	private:
		DirectX::XMFLOAT4 dummy1;
		DirectX::XMFLOAT4 dummy2;
		DirectX::XMFLOAT4 dummy3;
	};
}

#endif//__MugenEngine_GraphicStruct__