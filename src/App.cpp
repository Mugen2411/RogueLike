#include "App.h"
#include "Graphic/General.h"

namespace mugen_engine {

LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (msg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, msg, wparam, lparam);
}

App::App(const int width, const int height, const TCHAR* app_name)
    : width_(width), height_(height), app_name_(app_name) {}
void App::Run() {
  WNDCLASSEX wc = {};
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.lpfnWndProc = WindowProc;
  wc.lpszClassName = reinterpret_cast<LPCWSTR>(app_name_);
  wc.hInstance = GetModuleHandle(nullptr);
  RegisterClassEx(&wc);
  RECT wrc = {0, 0, width_, height_};
  AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, NULL);
  hwnd_ = CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, wrc.right - wrc.left,
                       wrc.bottom - wrc.top, nullptr, nullptr, wc.hInstance,
                       nullptr);

  Graphic::GetIns().Initialize(width_, height_, hwnd_);
  ShowWindow(hwnd_, SW_SHOW);
  MSG msg = {};
  while (true) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    if (msg.message == WM_QUIT) break;
  }
  UnregisterClass(wc.lpszClassName, wc.hInstance);
}
}  // namespace mugen_engine