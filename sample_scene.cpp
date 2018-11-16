#include "sample_scene.h"
#include "oak/core/entity.h"
#include "oak/core/sprite.h"
#include "move_script.h"
#include "oak/core/oakitus.h"

using namespace oak;
using namespace game;

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

void SampleScene::onLoad()
{
  Entity* ent = new Entity();
  Sprite* s = new Sprite("face.png", 0, 00, 1000, 1000, NULL);
  ent->addComponent(*s);
  Script* move = new MoveScript();
  ent->addScript(*move);

  Entity* ground = new Entity();
  ground->position.x = 0.5f;
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, NULL);
  ground->addComponent(*groundSprite);
  ground->layerID = -1;
}

void SampleScene::onUnload()
{
  Oakitus::deleteAllEnts();
}