//! @file GraphicCommandList.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MugenEngine_GraphicCommandList__
#define __MugenEngine_GraphicCommandList__

#include <d3d12.h>

#include <wrl/client.h>

namespace mugen_engine
{
	class MEGraphicDevice;

	/**********************************************************************//**
		@class		MEGraphicCommandList
		@brief		GPU�R�}���h���Ǘ�����N���X
	*//***********************************************************************/
	class MEGraphicCommandList
	{
	public:
		/**********************************************************************//**
			@brief			�R���X�g���N�^
			@param			�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		MEGraphicCommandList();

		/**********************************************************************//**
			@brief			������
			@param[in]		device			DX12�f�o�C�X
			@return			�C���X�^���X
		*//***********************************************************************/
		void Initialize(const MEGraphicDevice& device);

		/**********************************************************************//**
			@brief			�R�}���h�����s����GPU�������I���܂őҋ@����
			@param[in]		�Ȃ�
			@return			�Ȃ�
		*//***********************************************************************/
		void Execute();

		/**********************************************************************//**
			@brief			�R�}���h�L���[�̐��|�C���^���擾
			@param			�Ȃ�
			@return			�R�}���h�L���[�̐��|�C���^
		*//***********************************************************************/
		ID3D12CommandQueue* const GetCommandQueue() const
		{
			return m_cmdQueue.Get();
		}

		/**********************************************************************//**
			@brief			�R�}���h���X�g�̐��|�C���^���擾
			@param			�Ȃ�
			@return			�R�}���h���X�g�̐��|�C���^
		*//***********************************************************************/
		ID3D12GraphicsCommandList* const GetCommandList() const
		{
			return m_cmdList.Get();
		}
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator = nullptr;		//!< �R�}���h�A���P�[�^�[
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_cmdList = nullptr;		//!< �R�}���h���X�g
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_cmdQueue = nullptr;				//!< �R�}���h�L���[

		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence = nullptr;						//!< �t�F���X
		UINT64 m_fenceVal = 0;														//!< �t�F���X�̐i�����Ǘ����鐔�l
	};
}

#endif//__MugenEngine_GraphicCommandList__