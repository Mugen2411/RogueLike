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
	class GraphicCommandList
	{
	public:
		//! �R���X�g���N�^
		GraphicCommandList();
		//! ������
		void Initialize(ID3D12Device* device);
	private:

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator = nullptr;		//!< �R�}���h�A���P�[�^�[
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList = nullptr;		//!< �R�}���h���X�g
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue = nullptr;				//!< �R�}���h�L���[
	};
}

#endif//__MugenEngine_GraphicCommandList__