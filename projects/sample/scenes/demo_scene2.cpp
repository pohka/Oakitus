#include "demo_scene2.h"
#include <oak/oak.h>
#include "../movement_cmd.h"
#include <oak/debug.h>
#include "../sample_def.h"
#include "../sample_gamemode.h"

using namespace sample;
using namespace oak;

DemoScene2::DemoScene2()
{
  precache.textures = {
    "dummy.png",
    "anim_test2.png"
  };
}

void DemoScene2::onLoad()
{
  SampleGameMode::addEvents();

  Entity* ent = new Entity();
  ent->addComponent(new Sprite("dummy.png", 160.0f, 160.0f));

  ent->create(0.0f, 0.0f);

  Actor* unit = new Actor();
  Animator* animator = new Animator(
    ANIM_ACT_IDLE,
    new SpriteAnimation(
      "anim_test2.png",
      0,
      192, 192,
      100, 100,
      0.04f,
      Resources::getDefaultShaderID(),
      14,
      0,
      true
    )
  );

  animator->addAnim(
    ANIM_ACT_RUN,
    new SpriteAnimation(
      "anim_test2.png",
      ANIM_PRIORITY_LOWEST,
      192, 192,
      100, 100,
      0.04f,
      Resources::getDefaultShaderID(),
      12,
      2,
      true
    )
  );

  unit->addComponent(animator);
  unit->position.x = 100.0f;
  unit->create();
  Player* player = PlayerResource::getLocalPlayer();
  player->assignActor(unit);

  Command* movement = new MovementCMD();
  player->addCommand(movement);
}

void DemoScene2::onUnload()
{
  Scene::onUnload();
  EventManager::removeAllEvents();
}