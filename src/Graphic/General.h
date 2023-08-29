#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <vector>

namespace mugen_engine {
using Microsoft::WRL::ComPtr;
class Graphic {
 public:
  static Graphic& GetIns() { return instance_; }
  void Initialize(int width, int height, HWND hwnd);
  void ClearScreen();
  void ScreenFlip();

  ~Graphic() {}

 private:
  static Graphic instance_;
  Graphic();
  ComPtr<ID3D12Device> dev_;
  ComPtr<IDXGIFactory6> dxgiFactory_;
  ComPtr<IDXGISwapChain4> swapchain_;

  ComPtr<ID3D12CommandAllocator> cmdAllocator_;
  ComPtr<ID3D12GraphicsCommandList> cmdList_;
  ComPtr<ID3D12CommandQueue> cmdQueue_;

  ComPtr<ID3D12DescriptorHeap> rtvHeaps_;

  ComPtr<ID3D12Fence> fence_;
  UINT64 fenceVal_ = 0;

  const int num_back_buffer = 2;
  std::vector<ComPtr<ID3D12Resource>> back_buffers_;

  void EnableDebugLayer();
  void InitDevice();
  void InitCommandList();
  void InitSwapChain(int width, int height, HWND hwnd);
  void InitFence();

  void SetResourceBarrier(D3D12_RESOURCE_STATES before,
                          D3D12_RESOURCE_STATES after);
};
}  // namespace mugen_engine
