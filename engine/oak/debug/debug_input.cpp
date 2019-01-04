#include <oak/build_def.h>
#ifdef DEBUG_MODE
#include "debug_input.h"
#include <oak/input/input.h>
#include <oak/ui/ui.h>
#include <oak/time/time.h>
#include <oak/debug.h>
#include <oak/build_def.h>

#ifdef PLATFORM_WINDOWS
  #include "windows.h"
  #include "psapi.h"
#endif

using namespace debug;
using namespace oak;
using namespace ion;

void DebugInput::process()
{
  //reload css
  if (Input::isKeyDown(KEYCODE_F8))
  {
    StyleLoader::reload();
  }

  //close window
  if (Input::isKeyDown(KEYCODE_F9))
  {
    Window::close();
  }

  //current memory use
  if (Input::isKeyDown(KEYCODE_F10))
  {
#ifdef PLATFORM_WINDOWS
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    double virtualMemUsedByMe = (double)pmc.WorkingSetSize;
    std::cout << "MEMORY:" << (virtualMemUsedByMe / 1024.0 / 1024.0) << "MB" << std::endl;
#endif
  }

  //pausing
  if (Input::isKeyDown(KEYCODE_F11))
  {
    Time::setIsPaused(!Time::getIsPaused());

    if (Time::getIsPaused())
    {
      LOG << "Game Paused";
    }
    else
    {
      LOG << "Game Continue";
    }
  }


  //log fps
  if (Input::isKeyDown(KEYCODE_F12))
  {
    int fps = Time::getFPSLimiter().getFPS();
    int max = Time::getFPSLimiter().getMaxFPS();
    bool isLimited = Time::getFPSLimiter().getIsLimitingFPS();
    if (isLimited && fps > max)
    {
      fps = max;
    }

    LOG << "FPS:" << fps << "/" << max;
  }
}
#endif