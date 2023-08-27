#pragma once
#include <Windows.h>
#include <tchar.h>

namespace mugen_engine {
class App {
 public:
  App(const int width, const int height, const TCHAR* app_name);

  void Run();

 private:
  HWND hwnd_;
  const int width_;
  const int height_;
  const TCHAR* app_name_;
};
}  // namespace mugen_engine
