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
		void Initialize(IDXGIFactory4* dxgiFactory, ID3D12CommandQueue* cmdQueue,
			HWND hwnd, const int window_width, const int window_height);
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapchain = nullptr;			//!< �X���b�v�`�F�C��
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeaps = nullptr;		//!< �����_�[�^�[�Q�b�g�q�[�v
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_backBuffers;		//!< �o�b�N�o�b�t�@
	};
}

#endif//__MugenEngine_GraphicRenderTarget__