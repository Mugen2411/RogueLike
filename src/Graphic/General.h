#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace mugen_engine {
using Microsoft::WRL::ComPtr;
class Graphic {
 public:
  static Graphic& GetIns() { return instance_; }
  void Initialize(int width, int height, HWND hwnd);

 private:
  static Graphic instance_;
  Graphic();
  ComPtr<ID3D12Device> dev_ = nullptr;
  ComPtr<IDXGIFactory6> dxgiFactory_ = nullptr;
  ComPtr<IDXGISwapChain4> swapchain_ = nullptr;

  ComPtr<ID3D12CommandAllocator> cmdAllocator_ = nullptr;
  ComPtr<ID3D12GraphicsCommandList> cmdList_ = nullptr;
  ComPtr<ID3D12CommandQueue> cmdQueue_ = nullptr;

  void EnableDebugLayer();
  void InitDevice();
  void InitCommandList();
  void InitSwapChain(int width, int height, HWND hwnd);
};
}  // namespace mugen_engine
