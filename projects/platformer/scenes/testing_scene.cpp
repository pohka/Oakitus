#include "testing_scene.h"
#include "../prefabs/a_player.h"
#include <oak/oak.h>
#include "../commands/plat_movement_cmd.h"
#include "../plat_consts.h"
#include <oak/tiles/world.h>

using namespace plat;
using namespace oak;
using namespace tile;

TestingScene::TestingScene()
{
  precache.textures = {
    "test_tilemap.png"
  };
}

TestingScene::~TestingScene()
{

}

void TestingScene::onLoad()
{
  World* world = new World(8, 32);

  Texture* tex = Resources::getTextureByName("test_tilemap.png");
  uint shaderID = Resources::getDefaultShaderID();

  //hardcoded loading of tiles
  for (unsigned int i = 0; i < 4; i++)
  {
    Tile* tile = new Tile(i+1, tex, i%2, i/2, shaderID, world->TILE_SIZE);
    world->addTile(tile);
  }

  Chunk* chunk = world->addChunk();
  chunk->table[0][0] = 1;

  world->create(0.0f, 0.0f);

  LOG << "Loading scene";

  APlayer* playerActor = new APlayer();
  playerActor->create(0.0f, 0.0f);

  Player* player = PlayerResource::getLocalPlayerBySlot(1);
  if (player != nullptr)
  {
    player->assignActor(playerActor);

    if (!player->hasCommand(COMMAND_MOVEMENT))
    {
      player->addCommand(new MovementCMD());
    }
  }
}