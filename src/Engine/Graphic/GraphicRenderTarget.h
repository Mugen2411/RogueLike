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
		//! �R���X�g���N�^
		MEGraphicRenderTarget();
		//! ������
		void Initialize(const MEGraphicDevice& device, ID3D12CommandQueue* cmdQueue,
			HWND hwnd, const int window_width, const int window_height);
		//! �o�b�N�o�b�t�@�̓��e���f�B�X�v���C�ɔ��f����
		void Present();
		//! �`��O�o���A
		void SetBarrierBeforeRender(MEGraphicDevice& device, MEGraphicCommandList& cmdList);
		//! �v���[���g�O�o���A
		void SetBarrierBeforePresent(MEGraphicCommandList& cmdList);
		//! ��ʂ��w�肵���F�ŃN���A����
		void Clear(float clearColor[4], MEGraphicCommandList& cmdList);
	private:
		const int m_numBackBuffer;												//!< �o�b�N�o�b�t�@�̐�
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< �X���b�v�`�F�C��
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< �����_�[�^�[�Q�b�g�q�[�v
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< �o�b�N�o�b�t�@
		D3D12_CPU_DESCRIPTOR_HANDLE m_renderTargetHandle;						//!< OMSetRenderTarget�ɓn��CPU��̃A�h���X
		D3D12_VIEWPORT m_viewport;												//!< �r���[�|�[�g
	};
}

#endif//__MugenEngine_GraphicRenderTarget__