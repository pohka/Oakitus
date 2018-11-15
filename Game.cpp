#include "Game.h"

#include "core/Oakitus.h"
#include "core/Sprite.h"
#include "core/Entity.h"
#include "MoveScript.h"
#include "SampleScene.h"

using namespace game;
using namespace oak;

void Game::load()
{
  Scene* defaultScene = new SampleScene();
  Oakitus::setScene(*defaultScene);
}