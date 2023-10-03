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
#include <DirectXTex.h>
#include <d3dx12.h>

#include "Engine/Core.h"

/**
 *****************************************************************************
 * @brief	ウィンドウプロシージャ
 * @param	hwnd ウィンドウハンドル
 * @param	msg	メッセージ
 * @param	wparam	パラメータ
 * @param	lparam	パラメータ
 * @retval 0 正常終了
 * @retval 継続
 * @details
 *****************************************************************************
 */
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

/**
 *****************************************************************************
 * @brief	デバッグレイヤーを有効化
 * @details
 *****************************************************************************
 */
void EnableDebugLayer()
{
	ID3D12Debug* debugLayer = nullptr;
	auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
	debugLayer->EnableDebugLayer();
	debugLayer->Release();
}

/**
 *****************************************************************************
 * @brief	アライメントに揃える
 * @param size			元のサイズ
 * @param alignment		アライメントサイズ
 * @return				アライメントを揃えたサイズ
 *****************************************************************************
 */
size_t AlignmentedSize(size_t size, size_t alignment)
{
	return size + alignment - size % alignment;
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int window_width = 1280;
	int window_height = 720;
	WNDCLASSEX w = {};
	w.cbSize = sizeof(w);
	w.lpfnWndProc = WindowProcedure;
	w.lpszClassName = _T("RogueLike Magician");
	w.hInstance = GetModuleHandle(nullptr);

	RegisterClassEx(&w);

	RECT wrc = { 0, 0, window_width, window_height};
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindow(w.lpszClassName, _T("MagicaRogue"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		wrc.right - wrc.left, wrc.bottom - wrc.top,
		nullptr, nullptr, w.hInstance, nullptr);

	ShowWindow(hwnd, SW_SHOW);
	/*
#ifdef _DEBUG
	EnableDebugLayer();
#endif

	//DX12 1つだけあれば良さそうなモノ
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> basicDescHeap = nullptr;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers(2);
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelinestate = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature = nullptr;
	D3D12_VIEWPORT viewport = {};
	D3D12_RECT scissorrect = {};
	//DX12 描画する物毎に用意されるもの
	struct VERTEX_DATA
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
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
	Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuff = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	Microsoft::WRL::ComPtr<ID3D12Resource> idxBuff = nullptr;
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff = nullptr;
	struct TexRGBA
	{
		uint8_t R, G, B, A;
	};
	DirectX::TexMetadata metadata = {};
	DirectX::ScratchImage scratchImg = {};
	DirectX::Image const * img = {};
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff = nullptr;
	DirectX::XMMATRIX matrix = DirectX::XMMatrixScaling(2.0 / window_width, 2.0 / window_height, 1.0f);

	
	//DX12 スワップチェイン
	{
		DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

		swapchainDesc.Width = window_width;
		swapchainDesc.Height = window_height;
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchainDesc.Stereo = false;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapchainDesc.BufferCount = 2;
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		auto result = m_dxgiFactory->CreateSwapChainForHwnd(cmdQueue.Get(), hwnd, &swapchainDesc,
			nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapchain.ReleaseAndGetAddressOf()));
	}
	//DX12 ディスクリプタヒープ
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 2;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		auto result = m_device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(rtvHeaps.ReleaseAndGetAddressOf()));

		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		swapchain->GetDesc(&swcDesc);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();

		for(int idx = 0; idx < swcDesc.BufferCount; ++idx)
		{
			result = swapchain->GetBuffer(idx, IID_PPV_ARGS(backBuffers[idx].ReleaseAndGetAddressOf()));
			m_device->CreateRenderTargetView(backBuffers[idx].Get(), nullptr, handle);
			handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}

	//画像読み込み
	{
		DirectX::LoadFromWICFile(L"media/graphic/return_to_escape.png", DirectX::WIC_FLAGS_NONE, &metadata, scratchImg);
		img = scratchImg.GetImage(0, 0, 0);
	}

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
	//アップロード用中間バッファ
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = AlignmentedSize(img->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * img->height;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(uploadBuff.ReleaseAndGetAddressOf()));
	}
	//コピー先リソース
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_DEFAULT;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
		resdesc.Width = metadata.width;
		resdesc.Height = metadata.height;
		resdesc.DepthOrArraySize = metadata.arraySize;
		resdesc.MipLevels = metadata.mipLevels;
		resdesc.Format = metadata.format;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		auto result = m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc, 
			D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(texBuff.ReleaseAndGetAddressOf()));

		uint8_t* mapforImg = nullptr;
		result = uploadBuff->Map(0, nullptr, (void**)&mapforImg);

		auto srcAddress = img->pixels;
		auto rowPitch = AlignmentedSize(img->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
		for(int y = 0; y < img->height; ++y)
		{
			std::copy_n(srcAddress, rowPitch, mapforImg);
			srcAddress += img->rowPitch;
			mapforImg += rowPitch;
		}
		uploadBuff->Unmap(0, nullptr);
	}
	//GPUにテクスチャをアップロード
	{
		D3D12_TEXTURE_COPY_LOCATION src = {};
		src.pResource = uploadBuff.Get();
		src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset = 0;
		src.PlacedFootprint.Footprint.Width = metadata.width;
		src.PlacedFootprint.Footprint.Height = metadata.height;
		src.PlacedFootprint.Footprint.Depth = metadata.depth;
		src.PlacedFootprint.Footprint.RowPitch = AlignmentedSize(img->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
		src.PlacedFootprint.Footprint.Format = img->format;

		D3D12_TEXTURE_COPY_LOCATION dst = {};
		dst.pResource = texBuff.Get();
		dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex = 0;

		cmdList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

		//テクスチャ転送前バリア
		{
			D3D12_RESOURCE_BARRIER barrierDesc = {};
			barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrierDesc.Transition.pResource = texBuff.Get();
			barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
			barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

			cmdList->ResourceBarrier(1, &barrierDesc);
		}
		
	}
	//定数バッファ
	{
		auto heapprop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto resDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(matrix) + 0xFF) & ~0xFF);
		m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resDesc, 
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));

		//定数バッファへの書き込み
		DirectX::XMMATRIX* mapMatrix = nullptr;
		constBuff->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = matrix;
	}
	//定数バッファ
	{
		D3D12_HEAP_PROPERTIES heapprop = {};
		heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapprop.CreationNodeMask = 0;
		heapprop.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resdesc = {};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = (sizeof(matrix) + 0xFF) & ~0xFF;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.Format = DXGI_FORMAT_UNKNOWN;
		resdesc.SampleDesc.Count = 1;
		resdesc.SampleDesc.Quality = 0;
		resdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		auto result = m_device->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));

		DirectX::XMMATRIX* mapMatrix;
		result = constBuff->Map(0, nullptr, (void**)&mapMatrix);
		*mapMatrix = matrix;
		constBuff->Unmap(0, nullptr);
	}
	//ディスクリプタヒープ
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = 2;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		auto result = m_device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(basicDescHeap.ReleaseAndGetAddressOf()));
	}
	//シェーダーリソースビュー
	{
		auto basicHeapHandle = basicDescHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = metadata.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		auto handle = basicDescHeap->GetCPUDescriptorHandleForHeapStart();
		m_device->CreateShaderResourceView(texBuff.Get(), &srvDesc, handle);

		handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = constBuff->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = constBuff->GetDesc().Width;

		m_device->CreateConstantBufferView(&cbvDesc, handle);
	}

	//Blobのエラー処理
	auto processBlobError = [&](HRESULT result)
	{
		if(SUCCEEDED(result))
		{
			return;
		}
		if(result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("ファイルが見当たりません");
			return;
		}
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n(reinterpret_cast<char*>(errorBlob->GetBufferPointer()), errorBlob->GetBufferSize(), errstr.begin());
		errstr += '\n';
		::OutputDebugStringA(errstr.c_str());
	};

	//シェーダーオブジェクトの読み込み
	{
		auto result = D3DCompileFromFile(L"shader/BasicVertexShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "BasicVS", "vs_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, vsBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
		processBlobError(result);
		result = D3DCompileFromFile(L"shader/BasicPixelShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "BasicPS", "ps_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, psBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
		processBlobError(result);
	}

	//ルートシグネチャ
	{
		Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr;
		//サンプラー
		D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		//ディスクリプタレンジ
		D3D12_DESCRIPTOR_RANGE descTblRange[2] = {};
		//テクスチャ用
		descTblRange[0].NumDescriptors = 1;
		descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descTblRange[0].BaseShaderRegister = 0;
		descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//定数用
		descTblRange[1].NumDescriptors = 1;
		descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		descTblRange[1].BaseShaderRegister = 0;
		descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		//ルートパラメーター
		D3D12_ROOT_PARAMETER rootparam = {};
		//テクスチャ用
		rootparam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootparam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootparam.DescriptorTable.pDescriptorRanges = descTblRange;
		rootparam.DescriptorTable.NumDescriptorRanges = 2;
		//ルートシグネチャ
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		rootSignatureDesc.pParameters = &rootparam;
		rootSignatureDesc.NumParameters = 1;
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
		auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
			rootSigBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
		processBlobError(result);
		result = m_device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(rootsignature.ReleaseAndGetAddressOf()));
	}

	//パイプラインステート
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
		//ルートシグネチャ
		gpipeline.pRootSignature = rootsignature.Get();
		//シェーダー設定
		gpipeline.VS.pShaderBytecode = vsBlob->GetBufferPointer();
		gpipeline.VS.BytecodeLength = vsBlob->GetBufferSize();
		gpipeline.PS.pShaderBytecode = psBlob->GetBufferPointer();
		gpipeline.PS.BytecodeLength = psBlob->GetBufferSize();
		//サンプルマスク
		gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		//ラスタライザーステート
		gpipeline.RasterizerState.MultisampleEnable = false;
		gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		gpipeline.RasterizerState.DepthClipEnable = true;
		//ブレンドステート
		gpipeline.BlendState.AlphaToCoverageEnable = false;
		gpipeline.BlendState.IndependentBlendEnable = false;

		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
		renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		gpipeline.BlendState.RenderTarget[0] = renderTargetBlendDesc;
		//入力レイアウト
		gpipeline.InputLayout.pInputElementDescs = inputLayout;
		gpipeline.InputLayout.NumElements = _countof(inputLayout);
		gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		//レンダーターゲット
		gpipeline.NumRenderTargets = 1;
		gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		//アンチエイリアス
		gpipeline.SampleDesc.Count = 1;
		gpipeline.SampleDesc.Quality = 0;

		auto result = m_device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(pipelinestate.ReleaseAndGetAddressOf()));
	}
	//ビューポートとシザー矩形
	{
		viewport.Width = window_width;
		viewport.Height = window_height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;

		scissorrect.top = 0;
		scissorrect.left = 0;
		scissorrect.right = scissorrect.left + window_width;
		scissorrect.bottom = scissorrect.top + window_height;
	}*/

	mugen_engine::MECore::GetIns().Initialize(window_width, window_height);

	MSG msg = {};

	while(true)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			break;
		}
		/*
		//DX12 描画前処理
		{
			//auto result = cmdAllocator->Reset();
			auto bbIdx = swapchain->GetCurrentBackBufferIndex();
			auto rtvH = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
			rtvH.ptr += bbIdx * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			
			cmdAllocator->Reset();
			cmdList->Reset(cmdAllocator.Get(), nullptr);

			//DX12 レンダーターゲット前バリア
			{
				D3D12_RESOURCE_BARRIER BarrierDesc = {};
				BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				BarrierDesc.Transition.pResource = backBuffers[bbIdx].Get();
				BarrierDesc.Transition.Subresource = 0;
				BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
				BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
				cmdList->ResourceBarrier(1, &BarrierDesc);
			}
			cmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);
			float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
			cmdList->RSSetViewports(1, &viewport);
		}
		cmdList->SetPipelineState(pipelinestate.Get());
		cmdList->SetGraphicsRootSignature(rootsignature.Get());
		cmdList->SetDescriptorHeaps(1, basicDescHeap.GetAddressOf());
		cmdList->SetGraphicsRootDescriptorTable(0, basicDescHeap->GetGPUDescriptorHandleForHeapStart());
		cmdList->RSSetScissorRects(1, &scissorrect);
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmdList->IASetVertexBuffers(0, 1, &vbView);
		cmdList->IASetIndexBuffer(&ibView);
		cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

		{
			//DX12 プレゼント前バリア
			{
				auto bbIdx = swapchain->GetCurrentBackBufferIndex();
				D3D12_RESOURCE_BARRIER BarrierDesc = {};
				BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				BarrierDesc.Transition.pResource = backBuffers[bbIdx].Get();
				BarrierDesc.Transition.Subresource = 0;
				BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
				BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
				cmdList->ResourceBarrier(1, &BarrierDesc);
			}

			cmdList->Close();
			ID3D12CommandList* cmdLists[] = { cmdList.Get() };
			cmdQueue->ExecuteCommandLists(1, cmdLists);

			//待機処理
			cmdQueue->Signal(fence.Get(), ++fenceVal);
			if(fence->GetCompletedValue() != fenceVal)
			{
				auto event = CreateEvent(nullptr, false, false, nullptr);
				fence->SetEventOnCompletion(fenceVal, event);
				WaitForSingleObject(event, INFINITE);
				CloseHandle(event);
			}
			swapchain->Present(1, 0);
		}*/
	}

	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}