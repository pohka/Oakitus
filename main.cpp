#include <oak/oak_setup.h>

//#include "projects/rpg/load_rpg_game.h"
#include "projects/sample/load_game.h"

using namespace oak;


int main()
{
  uint windowW = 1066;
  uint windowH = 600;

  uint viewportW = 736;
  uint viewportH = 414;

  Oakitus::init(viewportW, viewportH, windowW, windowH, false);


  return 0;
}
