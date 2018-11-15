#include "game.h"

#include "core/oakitus.h"
#include "core/sprite.h"
#include "core/entity.h"
#include "move_script.h"
#include "sample_scene.h"

using namespace game;
using namespace oak;

void Game::load()
{
  Scene* defaultScene = new SampleScene();
  Oakitus::setScene(*defaultScene);
}