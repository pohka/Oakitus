#include "oak/oak.h"
#include "oak/game.h"

#include "sample_scene.h"
#include "map_loader.h"



using namespace game;
using namespace oak;

void Game::load()
{

  Scene* defaultScene = new SampleScene();
  Store::loadFirstScene(*defaultScene);

  MapLoader::loadMap("map.xml");
}
