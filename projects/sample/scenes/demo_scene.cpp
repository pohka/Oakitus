#include "demo_scene.h"
#include "../movement_cmd.h"
#include "../sample_def.h"
#include "../sample_gamemode.h"

using namespace sample;
using namespace oak;

DemoScene::DemoScene()
{
  precache.textures = {
    "face.png",
    "anim_test2.png"
  };
}

void DemoScene::onLoad()
{
  SampleGameMode::addEvents();

  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  
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

  if (player->hasCommand(COMMAND_MOVEMENT) == false)
  {
    Command* movement = new MovementCMD();
    player->addCommand(movement);
  }
}
