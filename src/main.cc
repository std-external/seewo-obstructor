#include <atomic>
#include <print>
#include <stacktrace>
#include <thread>

#include "blook/misc.h"
#include "screen_capture/BitBlt.h"
#include "seewo/iot_mqtt.h"

#include "blook/blook.h"

#include "Windows.h"

namespace seeob {

void init() {
  AllocConsole();
  freopen("conout$", "w", stdout);
  freopen("conout$", "w", stderr);
  ShowWindow(GetConsoleWindow(), SW_HIDE);

  auto proc = blook::Process::self();
  auto entryHook = proc->process_module().value()->entry_point()->inline_hook();

  std::println("[SeeOb] Loaded!");

  blook::misc::install_optimize_dll_hijacking("winhttp.dll");
  static std::atomic_bool initialized = false;
  auto init = []() {
    if (initialized.exchange(true))
      return;
    try {
      std::println("[SeeOb] Initializing...");
      seeob::screen::BitBlt::install();
      seeob::seewo::IotMqtt::install();
      std::println("[SeeOb] Everything done.");
    } catch (const std::exception &e) {
      std::println("[SeeOb] Error: {}\n{}", e.what(),
                   std::stacktrace::current());
    }
  };
  entryHook->install([=]() {
    init();
    return entryHook->call_trampoline<void>();
  });

  std::thread([=]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    init();
  }).detach();
}
}; // namespace seeob

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    seeob::init();
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;

  case DLL_PROCESS_DETACH:

    if (lpvReserved != nullptr) {
      break; // do not do cleanup if process termination scenario
    }

    // Perform any necessary cleanup.
    break;
  }
  return TRUE; // Successful DLL_PROCESS_ATTACH.
}