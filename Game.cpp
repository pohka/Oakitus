#include "game.h"

#include "oak/core/oakitus.h"
#include "oak/core/sprite.h"
#include "oak/core/entity.h"
#include "move_script.h"
#include "sample_scene.h"

using namespace game;
using namespace oak;

void Game::load()
{
  Scene* defaultScene = new SampleScene();
  Oakitus::setScene(*defaultScene);
}