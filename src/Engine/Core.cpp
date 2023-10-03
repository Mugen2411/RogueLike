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
	MECore& MECore::GetIns()
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
		m_graphicDevice.Initialize(window_width, window_height);
		m_graphicCommandList.Initialize(m_graphicDevice.GetDevice());
	}

	/**********************************************************************//**
		@brief			�R���X�g���N�^
		@param			�Ȃ�
		@return			�Ȃ�
	*//***********************************************************************/
	MECore::MECore()
	{}
}
