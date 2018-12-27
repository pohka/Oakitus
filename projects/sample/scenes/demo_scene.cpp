#include "demo_scene.h"
#include <oak/oak.h>

using namespace puz;
using namespace oak;


void DemoScene::onLoad()
{
  Resources::addTexture("face.png");
  Resources::addTexture("anim_test2.png");
  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  Animator* animator = new Animator(
    1,
    new SpriteAnimation(
      "anim_test2.png",
      0,
      192, 192,
      100, 100,
      0.04f,
      "default",
      14,
      0,
      true
    )
  );
  ent->addComponent(animator);

  ent->create(0.0f, 0.0f);
}