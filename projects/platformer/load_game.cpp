#include <oak/oak_setup.h>
#include "scenes/game_scenes.h"

using namespace oak;
using namespace plat;

void Oakitus::load()
{
  SceneManager::loadFirstScene(new TestingScene());
}