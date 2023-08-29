#include "General.h"

#include <string>

namespace mugen_engine {
Graphic Graphic::instance_;

Graphic::Graphic() : back_buffers_(num_back_buffer) {}

void Graphic::Initialize(int width, int height, HWND hwnd) {
#ifdef _DEBUG
  EnableDebugLayer();
#endif
  InitDevice();
  InitCommandList();
  InitSwapChain(width, height, hwnd);
  InitFence();
}

void Graphic::ClearScreen() {
  SetResourceBarrier(D3D12_RESOURCE_STATE_PRESENT,
                     D3D12_RESOURCE_STATE_RENDER_TARGET);

  auto bbIdx = swapchain_->GetCurrentBackBufferIndex();
  auto rtvH = rtvHeaps_->GetCPUDescriptorHandleForHeapStart();
  rtvH.ptr += bbIdx * dev_->GetDescriptorHandleIncrementSize(
                          D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  cmdList_->OMSetRenderTargets(1, &rtvH, true, nullptr);

  float clearColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
  cmdList_->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
}

void Graphic::ScreenFlip() {
  SetResourceBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET,
                     D3D12_RESOURCE_STATE_PRESENT);

  cmdList_->Close();
  ID3D12CommandList* cmdlists[] = {cmdList_.Get()};
  cmdQueue_->ExecuteCommandLists(1, cmdlists);

  cmdQueue_->Signal(fence_.Get(), ++fenceVal_);
  auto event = CreateEvent(nullptr, false, false, nullptr);
  fence_->SetEventOnCompletion(fenceVal_, event);
  WaitForSingleObject(event, INFINITE);
  CloseHandle(event);

  swapchain_->Present(0, 0);

  cmdAllocator_->Reset();
  cmdList_->Reset(cmdAllocator_.Get(), nullptr);
}

void Graphic::EnableDebugLayer() {
  ID3D12Debug* debugLayer = nullptr;
  auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
  debugLayer->EnableDebugLayer();
  debugLayer->Release();
}

void Graphic::InitDevice() {
  D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0,
                                D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
  D3D_FEATURE_LEVEL feature_level;
  for (auto lv : levels) {
    if (SUCCEEDED(D3D12CreateDevice(nullptr, lv,
                                    IID_PPV_ARGS(dev_.GetAddressOf())))) {
      feature_level = lv;
      break;
    }
  }

#ifdef _DEBUG
  if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG,
                                IID_PPV_ARGS(dxgiFactory_.GetAddressOf())))) {
    abort();
  }
#else
  if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(dxgiFactory_.GetAddressOf())))) {
    abort();
  }
#endif
  std::vector<ComPtr<IDXGIAdapter>> adapters;
  ComPtr<IDXGIAdapter> tmpAdpt = nullptr;
  for (int i = 0;
       dxgiFactory_->EnumAdapters(i, &tmpAdpt) != DXGI_ERROR_NOT_FOUND; ++i) {
    adapters.push_back(tmpAdpt);
  }

  for (auto adpt : adapters) {
    DXGI_ADAPTER_DESC adesc = {};
    adpt->GetDesc(&adesc);

    std::wstring strDesc = adesc.Description;

    if (strDesc.find(L"NVIDIA") != std::string::npos) {
      tmpAdpt = adpt;
      break;
    }
  }
}
void Graphic::InitCommandList() {
  if (FAILED(dev_->CreateCommandAllocator(
          D3D12_COMMAND_LIST_TYPE_DIRECT,
          IID_PPV_ARGS(cmdAllocator_.GetAddressOf()))))
    abort();
  if (FAILED(dev_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                     cmdAllocator_.Get(), nullptr,
                                     IID_PPV_ARGS(cmdList_.GetAddressOf()))))
    abort();

  D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
  cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  cmdQueueDesc.NodeMask = 0;
  cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
  cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  if (FAILED(dev_->CreateCommandQueue(&cmdQueueDesc,
                                      IID_PPV_ARGS(cmdQueue_.GetAddressOf()))))
    abort();
}
void Graphic::InitSwapChain(int width, int height, HWND hwnd) {
  DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
  swapchainDesc.Width = width;
  swapchainDesc.Height = height;
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
  auto res = dxgiFactory_->CreateSwapChainForHwnd(
      cmdQueue_.Get(), hwnd, &swapchainDesc, nullptr, nullptr,
      reinterpret_cast<IDXGISwapChain1**>(swapchain_.GetAddressOf()));
  if (FAILED(res)) abort();

  D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
  heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  heapDesc.NodeMask = 0;
  heapDesc.NumDescriptors = 2;
  heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

  if (FAILED(dev_->CreateDescriptorHeap(
          &heapDesc, IID_PPV_ARGS(rtvHeaps_.GetAddressOf()))))
    abort();

  auto handle = rtvHeaps_->GetCPUDescriptorHandleForHeapStart();
  for (int idx = 0; idx < swapchainDesc.BufferCount; ++idx) {
    swapchain_->GetBuffer(idx, IID_PPV_ARGS(back_buffers_[idx].GetAddressOf()));
    handle.ptr += idx * dev_->GetDescriptorHandleIncrementSize(
                            D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    dev_->CreateRenderTargetView(back_buffers_[idx].Get(), nullptr, handle);
  }
}

void Graphic::InitFence() {
  if (FAILED(dev_->CreateFence(fenceVal_, D3D12_FENCE_FLAG_NONE,
                               IID_PPV_ARGS(fence_.GetAddressOf()))))
    abort();
}

void Graphic::SetResourceBarrier(D3D12_RESOURCE_STATES before,
                                 D3D12_RESOURCE_STATES after) {
  auto bbIdx = swapchain_->GetCurrentBackBufferIndex();

  D3D12_RESOURCE_BARRIER barrierDesc = {};
  barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrierDesc.Transition.pResource = back_buffers_[bbIdx].Get();
  barrierDesc.Transition.Subresource = 0;
  barrierDesc.Transition.StateBefore = before;
  barrierDesc.Transition.StateAfter = after;

  cmdList_->ResourceBarrier(1, &barrierDesc);
}
}  // namespace mugen_engine