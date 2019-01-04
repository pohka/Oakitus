#include <oak/oak_setup.h>

//#include "projects/rpg/load_rpg_game.h"
//#include "projects/sample/load_game.h"

using namespace oak;

#ifdef DEBUG_MODE
  #include <iostream>


int main()
{
  std::cout << "----- DEBUG MODE ENABLED -----" << std::endl;

  Oakitus::init();
  return 0;
}
#else
  #ifdef PLATFORM_WINDOWS
  INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
  {
    Oakitus::init();
    return 0;
  }
  #endif
#endif