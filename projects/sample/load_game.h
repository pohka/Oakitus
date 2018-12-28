#include <oak/oak_setup.h>
//#include <oak/ui/ui.h>
#include <oak/debug.h>
#include <oak/oak.h>
#include "scenes/game_scenes.h"

using namespace sample;

void oak::Oakitus::load()
{
  BasePlayer* player1 = new BasePlayer();
  PlayerResource::addPlayer(player1);

  Scene* scene = new DemoScene();
  Scene::loadFirstScene(scene);
}
