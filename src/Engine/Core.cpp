#include "Core.h"
//! @file Core.cpp
//! @note Copyright (c) Mugen_GameLab

namespace mugen_engine
{
	/**********************************************************************//**
		@brief			�C���X�^���X�̎擾
		@param			�Ȃ�
		@return			�C���X�^���X
	*//***********************************************************************/
	MECore& MECore::GetIns() const
	{
		static MECore instance;
		return instance;
	}

	/**********************************************************************//**
		@brief			������
		@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
		@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
		@return			�C���X�^���X
	*//***********************************************************************/
	void MECore::Initialize(const int window_width, const int window_height)
	{
		graphicCore.Initialize(window_width, window_height);
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MECore::MECore()
	{}
}