
#include <oak/oak_setup.h>
#include "scenes/scene_1.h"

using namespace oak;
using namespace chess;

void Oakitus::load()
{
  SceneManager::loadFirstScene(new Scene1());
}
