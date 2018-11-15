#include "sample_scene.h"
#include "core/entity.h"
#include "core/sprite.h"
#include "move_script.h"
#include "core/oakitus.h"

using namespace oak;
using namespace game;

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

void SampleScene::onLoad()
{
  Entity* ent = new Entity();
  Sprite* s = new Sprite("face.png", 0, 500, 700, 500, NULL);
  ent->addComponent(*s);
  Script* move = new MoveScript();
  ent->addScript(*move);
}

void SampleScene::onUnload()
{
  Oakitus::deleteAllEnts();
}