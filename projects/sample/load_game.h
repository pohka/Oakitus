#include <oak/oak_setup.h>
//#include <oak/ui/ui.h>
#include <oak/oak.h>
#include "scenes/game_scenes.h"

using namespace sample;
using namespace oak;

void Oakitus::load()
{
  Scene* scene = new DemoScene2();
  SceneManager::loadFirstScene(scene);
}
