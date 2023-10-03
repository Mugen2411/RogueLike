//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCommandList__
#define __MugenEngine_GraphicCommandList__

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	/**********************************************************************//**
		@class		MEGraphicCommandList
		@brief		GPU�R�}���h���Ǘ�����N���X
	*//***********************************************************************/
	class MEGraphicCommandList
	{
	public:
		//! �R���X�g���N�^
		MEGraphicCommandList();
		//! ������
		void Initialize(ID3D12Device * const device);
		//! ���s&GPU������ҋ@
		void Execute();
		//! �R�}���h�L���[�̐��|�C���^���擾
		ID3D12CommandQueue * const GetCommandQueue() const;
		//! �R�}���h���X�g�̐��|�C���^���擾
		ID3D12GraphicsCommandList* const GetCommandList() const;
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;		//!< �R�}���h�A���P�[�^�[
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;		//!< �R�}���h���X�g
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;				//!< �R�}���h�L���[

		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence = nullptr;						//!< �t�F���X
		UINT64 m_fenceVal = 0;														//!< �t�F���X�̐i�����Ǘ����鐔�l
	};
}

#endif//__MugenEngine_GraphicCommandList__