#include "BitBlt.h"
#include <cstddef>
#include <fstream>
#include <optional>
#include <print>
#include <vector>

#include "blook/blook.h"

#include "Windows.h"
#include "blook/function.h"
#include "blook/memo.h"
#include "wingdi.h"
namespace seeob::screen {
HDC getFakeDC() {
  static std::optional<HDC> fakeDC;

  if (!fakeDC) {
    HDC screenDC = GetDC(0);
    if (screenDC) {
      fakeDC = CreateCompatibleDC(screenDC);
      ReleaseDC(0, screenDC);
    }

    if (!fakeDC) {
      std::println("Failed to create compatible DC");
    }
  }

  return fakeDC.value_or(nullptr);
}

void BitBlt::install() {
  auto proc = blook::Process::self();
  auto gdi32 = proc->module("gdi32.dll");
  if (!gdi32) {
    std::println("[Bitblt] Failed to get gdi32.dll module");
    return;
  }

  auto bitBltExport = gdi32.value()->exports("BitBlt");
  if (!bitBltExport) {
    std::println("[Bitblt] Failed to find BitBlt export");
    return;
  }

  auto hook = bitBltExport.value().inline_hook();
  hook->install([=](HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1,
                    int y1, DWORD rop) {
    return hook->call_trampoline<size_t>(getFakeDC(), x, y, cx, cy, hdcSrc, x1,
                                         y1, rop);
  });
}
}; // namespace seeob::screen