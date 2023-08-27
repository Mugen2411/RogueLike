#include <Windows.h>
#include <tchar.h>

#include "App.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC) {
  auto app = mugen_engine::App(1280, 960, _T("ローグライク"));
  app.Run();
  return 0;
}