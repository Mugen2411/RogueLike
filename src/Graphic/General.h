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

  void EnableDebugLayer();
  void InitDevice();
  void InitCommandList();
  void InitSwapChain(int width, int height, HWND hwnd);
};
}  // namespace mugen_engine
