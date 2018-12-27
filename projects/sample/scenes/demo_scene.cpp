#include "demo_scene.h"
#include <oak/oak.h>

using namespace puz;
using namespace oak;


void DemoScene::onLoad()
{
  Resources::addTexture("face.png");
  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  ent->create(0.0f, 0.0f);
}