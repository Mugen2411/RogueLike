#include "General.h"

#include <string>
#include <vector>

namespace mugen_engine {
Graphic Graphic::instance_ = Graphic();

Graphic::Graphic() {}

void Graphic::Initialize(int width, int height, HWND hwnd) {
#ifdef _DEBUG
  EnableDebugLayer();
#endif
  InitDevice();
  InitCommandList();
  InitSwapChain(width, height, hwnd);
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
    if (D3D12CreateDevice(nullptr, lv, IID_PPV_ARGS(dev_.GetAddressOf())) ==
        S_OK) {
      feature_level = lv;
      break;
    }
  }

  #ifdef _DEBUG
  if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG ,IID_PPV_ARGS(dxgiFactory_.GetAddressOf())))) {
    abort();
  }
  #else
  if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(dxgiFactory_.GetAddressOf())))) {
    abort();
  }
  #endif
  std::vector<IDXGIAdapter*> adapters;
  IDXGIAdapter* tmpAdpt = nullptr;
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
}
}  // namespace mugen_engine