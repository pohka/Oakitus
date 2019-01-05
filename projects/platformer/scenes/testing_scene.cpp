#include "testing_scene.h"
#include "../prefabs/a_player.h"
#include <oak/oak.h>
#include "../commands/plat_movement_cmd.h"
#include "../plat_consts.h"
#include <oak/tiles/world.h>
#include "../prefabs/camera_ent.h"

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
  const uint CHUNK_SIZE = 32;
  const uint TILE_SIZE = 16;
  World* world = new World(TILE_SIZE, CHUNK_SIZE);

  //hardcoded loading of tiles
  Texture* tex = Resources::getTextureByName("test_tilemap.png");
  for (unsigned int i = 0; i < 4; i++)
  {
    Tile* tile = new Tile(i+1, tex, i%2, i/2, world->TILE_SIZE, 1);
    world->addTile(tile);
  }

  Chunk* chunk = world->addChunk();
  for (uint i = 0; i < CHUNK_SIZE; i++)
  {
    chunk->table[i][0] = 1;
    chunk->table[0][i] = 1;
    chunk->table[i][CHUNK_SIZE-1] = 1;
    chunk->table[CHUNK_SIZE-1][i] = 1;
  }
  world->create(0.0f, 0.0f);

  LOG << "Loading scene";

  //create camera
  Entity* cameraEnt = new CameraEnt();
  cameraEnt->create();

  //create player actor
  APlayer* playerActor = new APlayer();
  playerActor->create(0.0f, 0.0f);

  //set follow target
  auto follow = cameraEnt->getComponent<CameraFollow>();
  follow->setTarget(playerActor);

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