//! @file main.cpp
//! @note Copyright (c) Mugen_Gamelab

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <memory>

#include <wrl/client.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3dx12.h>

#include "Engine/Core.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	/*
	
	//DX12 描画する物毎に用意されるもの
	
	VERTEX_DATA vertices[4] =
	{
		{{-32.0f,-32.0f, 0.0f},{0.0f, 1.0f}},
		{{-32.0f, 32.0f, 0.0f},{0.0f, 0.0f}},
		{{ 32.0f,-32.0f, 0.0f},{1.0f, 1.0f}},
		{{ 32.0f, 32.0f, 0.0f},{1.0f, 0.0f}},
	};
	uint16_t indices[] = {
		0, 1, 2,
		2, 1, 3
	};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	Microsoft::WRL::ComPtr<ID3D12Resource> idxBuff = nullptr;
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff = nullptr;
	DirectX::XMMATRIX matrix = DirectX::XMMatrixScaling(2.0 / window_width, 2.0 / window_height, 1.0f);

	//頂点バッファ
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = sizeof(vertices);
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));

		//確保したGPUヒープに頂点データを流し込む
		VERTEX_DATA* vertMap = nullptr;
		result = vertBuff->Map(0, nullptr, reinterpret_cast<void**>(&vertMap));
		std::copy(std::begin(vertices), std::end(vertices), vertMap);
		vertBuff->Unmap(0, nullptr);
	}
	//頂点バッファビュー
	{
		vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
		vbView.SizeInBytes = sizeof(vertices);
		vbView.StrideInBytes = sizeof(vertices[0]);
	}
	//インデックスバッファ
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = sizeof(indices);
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(idxBuff.ReleaseAndGetAddressOf()));

		//確保したGPUヒープに頂点データを流し込む
		uint16_t* idxMap = nullptr;
		result = idxBuff->Map(0, nullptr, reinterpret_cast<void**>(&idxMap));
		std::copy(std::begin(indices), std::end(indices), idxMap);
		idxBuff->Unmap(0, nullptr);
	}
	//インデックスバッファビュー
	{
		ibView.BufferLocation = idxBuff->GetGPUVirtualAddress();
		ibView.SizeInBytes = sizeof(indices);
		ibView.Format = DXGI_FORMAT_R16_UINT;
	}
	//コピー先リソース
	{
		
	}
	//GPUにテクスチャをアップロード
	{
		
		
	}
	//定数バッファ
	{

		//定数バッファへの書き込み
		DirectX::XMMATRIX* mapMatrix = nullptr;
		constBuff->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = matrix;
	}
	//定数バッファ
	{
		DirectX::XMMATRIX* mapMatrix;
		result = constBuff->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = matrix;
		constBuff->Unmap(0, nullptr);
	}*/

	mugen_engine::MECore::GetIns().Initialize(L"MagicaRogue", window_width, window_height);

	mugen_engine::MECore::GetIns().LoadGraph("esc", L"media/graphic/return_to_escape.png");

	while(mugen_engine::MECore::GetIns().ProcessMessage() == 0)
	{
		mugen_engine::MECore::GetIns().ClearScreen(0, 0xFF, 0xFF);
		/*
		cmdList->SetPipelineState(pipelinestate.Get());
		cmdList->SetGraphicsRootSignature(rootsignature.Get());
		cmdList->SetDescriptorHeaps(1, m_basicDescHeap.GetAddressOf());
		cmdList->SetGraphicsRootDescriptorTable(0, m_basicDescHeap->GetGPUDescriptorHandleForHeapStart());
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmdList->IASetVertexBuffers(0, 1, &vbView);
		cmdList->IASetIndexBuffer(&ibView);
		cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
		*/

		mugen_engine::MECore::GetIns().ScreenFlip();
	}

	mugen_engine::MECore::GetIns().Finalize();

	return 0;
}