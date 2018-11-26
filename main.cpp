#include <oak_setup.h>
#include "scenes/main_scene.h"
#include <core/player_resource.h>
#include "player.h"

using namespace oak;
using namespace game;

int main()
{
  Oakitus::init();
  return 0;
}


void Oakitus::load()
{
  BasePlayer* player1 = new Player();
  PlayerResource::addPlayer(*player1);

  Scene* mainScene = new MainScene();
  Scene::loadFirstScene(*mainScene);
}

