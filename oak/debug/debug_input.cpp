#include "debug_input.h"
#include <core/input.h>
#include <ui/ui.h>

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
}