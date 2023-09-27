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

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

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

	RECT wrc = { 0,0,window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindow(w.lpszClassName, _T("RogueLikeMagician"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		wrc.right - wrc.left, wrc.bottom - wrc.top,
		nullptr, nullptr, w.hInstance, nullptr);

	ShowWindow(hwnd, SW_SHOW);

#ifdef _DEBUG
	EnableDebugLayer();
#endif

	//DX12 1つだけあれば良さそうなモノ
	Microsoft::WRL::ComPtr<ID3D12Device> _dev = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory6> _dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> _swapchain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _cmdAllocator = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _cmdList = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> _cmdQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvHeaps = nullptr;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> _backBuffers(2);
	Microsoft::WRL::ComPtr<ID3D12Fence> _fence = nullptr;
	UINT64 _fenceVal = 0;
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	//DX12 描画する物毎に用意されるもの
	DirectX::XMFLOAT3 vertices[3] =
	{
		{-1.0f, 1.0f, 0.0f},
		{-1.0f, 1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
	};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vbView = {};

	//DXGIファクトリ
	{
#ifdef _DEBUG
		auto result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
		auto result = CreateDXGIFactory1(IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif
	}

	//DX12 アダプタ列挙
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> adapters;
	Microsoft::WRL::ComPtr<IDXGIAdapter> tmpAdapter = nullptr;

	for(int i = 0; _dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(tmpAdapter);
	}

	for(auto adpt : adapters)
	{
		DXGI_ADAPTER_DESC adesc = {};
		adpt->GetDesc(&adesc);

		std::wstring strDesc(adesc.Description);
		if(strDesc.find(L"NVIDIA") != std::string::npos)
		{
			tmpAdapter = adpt;
			break;
		}
	}

	//DX12 デバイス初期化
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	D3D_FEATURE_LEVEL featureLevel;

	for(auto lv : levels)
	{
		if(D3D12CreateDevice(tmpAdapter.Get(), lv, IID_PPV_ARGS(_dev.ReleaseAndGetAddressOf())))
		{
			featureLevel = lv;
			break;
		}
	}

	//DX12 コマンドリストとコマンドアロケーター
	{
		auto result = _dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(_cmdAllocator.ReleaseAndGetAddressOf()));
	}
	{
		auto result = _dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAllocator.Get(),
			nullptr, IID_PPV_ARGS(_cmdList.ReleaseAndGetAddressOf()));
	}

	//DX12 コマンドキュー
	{
		D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
		cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		cmdQueueDesc.NodeMask = 0;
		cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		auto result = _dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(_cmdQueue.ReleaseAndGetAddressOf()));
	}
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
		swapchainDesc.Scaling = DXGI_SCALING_NONE;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		auto result = _dxgiFactory->CreateSwapChainForHwnd(_cmdQueue.Get(), hwnd, &swapchainDesc,
			nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(_swapchain.ReleaseAndGetAddressOf()));
	}
	//DX12 ディスクリプタヒープ
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 2;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		auto result = _dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(_rtvHeaps.ReleaseAndGetAddressOf()));

		DXGI_SWAP_CHAIN_DESC swcDesc = {};
		_swapchain->GetDesc(&swcDesc);

		D3D12_CPU_DESCRIPTOR_HANDLE handle = _rtvHeaps->GetCPUDescriptorHandleForHeapStart();

		for(int idx = 0; idx < swcDesc.BufferCount; ++idx)
		{
			result = _swapchain->GetBuffer(idx, IID_PPV_ARGS(_backBuffers[idx].ReleaseAndGetAddressOf()));
			_dev->CreateRenderTargetView(_backBuffers[idx].Get(), nullptr, handle);
			handle.ptr += _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}

	//フェンス
	{
		auto result = _dev->CreateFence(_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
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

		auto result = _dev->CreateCommittedResource(&heapprop, D3D12_HEAP_FLAG_NONE, &resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));

		//確保したGPUヒープに頂点データを流し込む
		DirectX::XMFLOAT3 *vertMap = nullptr;
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

	//シェーダーオブジェクトの読み込み
	{
		auto f = [&](HRESULT result)
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
		auto result = D3DCompileFromFile(L"shader/BasicVertexShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "BasicVS", "vs_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, psBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
		f(result);
		result = D3DCompileFromFile(L"shader/BasicPixelShader.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "BasicPS", "ps_5_0",
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, psBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
		f(result);
	}

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

		//DX12 描画前処理
		{
			//auto result = _cmdAllocator->Reset();
			auto bbIdx = _swapchain->GetCurrentBackBufferIndex();
			auto rtvH = _rtvHeaps->GetCPUDescriptorHandleForHeapStart();
			rtvH.ptr += bbIdx * _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			//DX12 レンダーターゲット前バリア
			{
				D3D12_RESOURCE_BARRIER BarrierDesc = {};
				BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				BarrierDesc.Transition.pResource = _backBuffers[bbIdx].Get();
				BarrierDesc.Transition.Subresource = 0;
				BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
				BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
				_cmdList->ResourceBarrier(1, &BarrierDesc);
			}
			_cmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);
			float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			_cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
		}

		//DX12 描画後処理
		{
			//DX12 プレゼント前バリア
			{
				auto bbIdx = _swapchain->GetCurrentBackBufferIndex();
				D3D12_RESOURCE_BARRIER BarrierDesc = {};
				BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				BarrierDesc.Transition.pResource = _backBuffers[bbIdx].Get();
				BarrierDesc.Transition.Subresource = 0;
				BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
				BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
				_cmdList->ResourceBarrier(1, &BarrierDesc);
			}

			_cmdList->Close();
			ID3D12CommandList* cmdLists[] = { _cmdList.Get() };
			_cmdQueue->ExecuteCommandLists(1, cmdLists);

			//待機処理
			_cmdQueue->Signal(_fence.Get(), ++_fenceVal);
			if(_fence->GetCompletedValue() != _fenceVal)
			{
				auto event = CreateEvent(nullptr, false, false, nullptr);
				_fence->SetEventOnCompletion(_fenceVal, event);
				WaitForSingleObject(event, INFINITE);
				CloseHandle(event);
			}
			_swapchain->Present(1, 0);

			_cmdAllocator->Reset();
			_cmdList->Reset(_cmdAllocator.Get(), nullptr);
		}
	}

	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}