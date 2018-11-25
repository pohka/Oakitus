//#include "oak/oak.h"
#include "oak/game.h"

#include "sample_scene.h"



using namespace game;
using namespace oak;

void Game::load()
{

  Scene* defaultScene = new SampleScene();
  Scene::loadFirstScene(*defaultScene);

  
}
