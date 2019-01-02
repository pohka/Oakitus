#include "debug_input.h"
#include <oak/core/input.h>
#include <oak/ui/ui.h>
#include <oak/core/time.h>
#include <oak/debug.h>

using namespace debug;
using namespace oak;
using namespace ion;

void DebugInput::process()
{
  //close window
  if (Input::isKeyDown(KEYCODE_F9))
  {
    Window::close();
  }

  //reload css
  if (Input::isKeyDown(KEYCODE_F8))
  {
    StyleLoader::reload();
  }

  //log fps
  if (Input::isKeyDown(KEYCODE_F12))
  {
    int fps = Time::getFPSLimiter().getFPS();
    int max = Time::getFPSLimiter().getMaxFPS();
    bool isLimited = Time::getFPSLimiter().getIsLimitingFPS();
    if(isLimited && fps > max)
    {
      fps = max;
    }

    LOG << "FPS:" << fps << "/" << max;
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
}