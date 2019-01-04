//enables debug mode in release builds
#define DEBUG_MODE_ENABLED

#include <oak/oak_setup.h>

//#include "projects/rpg/load_rpg_game.h"
#include "projects/sample/load_game.h"

using namespace oak;

#ifdef DEBUG_MODE
  #include <iostream>


int main()
{
#ifdef DEBUG_MODE
  std::cout << "in debug" << std::endl;
#else
  //std::cout << "not in debug" << std::endl;
#endif

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