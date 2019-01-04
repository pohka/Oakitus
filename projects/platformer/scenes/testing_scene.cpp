#include "testing_scene.h"
#include "../prefabs/a_player.h"
#include <oak/oak.h>
#include "../commands/plat_movement_cmd.h"
#include "../plat_consts.h"

using namespace plat;
using namespace oak;

TestingScene::TestingScene()
{
  precache.textures = {
    
  };
}

TestingScene::~TestingScene()
{

}

void TestingScene::onLoad()
{
  LOG << "Loading scene";

  APlayer* playerActor = new APlayer();
  playerActor->create(0.0f, 0.0f);

  Player* player = PlayerResource::getLocalPlayerBySlot(1);
  if (player != nullptr)
  {
    player->assignActor(playerActor);
    LOG << "assigned actor";

    if (!player->hasCommand(COMMAND_MOVEMENT))
    {
      player->addCommand(new MovementCMD());
    }
  }
}