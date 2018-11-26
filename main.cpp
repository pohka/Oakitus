#include <oak_setup.h>
#include "scenes/main_scene.h"
#include "player_resource.h"

using namespace oak;
using namespace game;

int main()
{
  Oakitus::init();
  return 0;
}


void Oakitus::load()
{
  PlayerResource::addPlayer();

  Scene::loadFirstScene(*new MainScene());
}

