#include "SampleScene.h"
#include "core/Entity.h"
#include "core/Sprite.h"
#include "MoveScript.h"
#include "core/Oakitus.h"

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