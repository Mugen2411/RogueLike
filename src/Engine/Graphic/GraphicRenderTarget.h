//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicRenderTarget__
#define __MugenEngine_GraphicRenderTarget__

#include "GraphicDevice.h"
#include "GraphicCommandList.h"

#include <vector>

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicRenderTarget
		@brief		�`��ΏۂƂȂ��ʂ��Ǘ�����N���X
	*//***********************************************************************/
	class MEGraphicRenderTarget
	{
	public:
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEGraphicRenderTarget();

		/**********************************************************************//**
			@brief			������
			@param[in]		device				�f�o�C�X
			@param[in]		cmdList				�R�}���h���X�g
			@param[in]		hwnd				�E�B���h�E�n���h��
			@param[in]		window_width		�E�B���h�E(�`��͈�)�̉���
			@param[in]		window_height		�E�B���h�E(�`��͈�)�̏c��
			@return			�C���X�^���X
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device, const MEGraphicCommandList& cmdList,
			HWND hwnd, const int window_width, const int window_height);

		/**********************************************************************//**
			@brief			�o�b�N�o�b�t�@�̓��e���f�B�X�v���C�ɔ��f����
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Present();

		/**********************************************************************//**
			@brief			�`��O�o���A
			@param			device			�f�o�C�X
			@param			cmdList			�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void SetBarrierBeforeRender(MEGraphicDevice& device, MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			�v���[���g�O�o���A
			@param			cmdList			�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void SetBarrierBeforePresent(MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			��ʂ��w�肵���F�ŃN���A����
			@param			clearColor		�w��F(RGBA, 0.0f�`1.0f)
			@param			cmdList			�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void Clear(float clearColor[4], MEGraphicCommandList& cmdList);

		/**********************************************************************//**
			@brief			�`��\�Ȕ͈͂�ݒ肷��
			@param			cmdList			�R�}���h���X�g
			@param[in]		topX			�����X���W
			@param[in]		topY			�����Y���W
			@param[in]		bottomX			�E����X���W
			@param[in]		bottomY			�E����Y���W
			@return			�Ȃ�
		*//***********************************************************************/
		void SetRenderArea(MEGraphicCommandList& cmdList, 
			const int topX, const int topY, const int bottomX, const int bottomY);

		/**********************************************************************//**
			@brief			�`�斈�ɕK�v�ȃR�}���h��ς�
			@param			cmdList			�R�}���h���X�g
			@return			�Ȃ�
		*//***********************************************************************/
		void SetRenderBaseCommand(MEGraphicCommandList& cmdList);
	private:
		const int m_numBackBuffer;												//!< �o�b�N�o�b�t�@�̐�
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< �X���b�v�`�F�C��
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< �����_�[�^�[�Q�b�g�q�[�v
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< �o�b�N�o�b�t�@
		D3D12_CPU_DESCRIPTOR_HANDLE m_renderTargetHandle;						//!< OMSetRenderTarget�ɓn��CPU��̃A�h���X
		D3D12_VIEWPORT m_viewport;												//!< �r���[�|�[�g
		D3D12_RECT m_scissorRect;												//!< �V�U�[��`
	};
}

#endif//__MugenEngine_GraphicRenderTarget__