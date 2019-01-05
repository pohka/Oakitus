#include "world.h"
#include <oak/tiles/chunk_script.h>
//#include <oak/collision/collision_rect.h>

using namespace tile;

World::World(
  const uint TILE_SIZE,
  const uint CHUNK_SIZE
) : 
  TILE_SIZE(TILE_SIZE),
  CHUNK_SIZE(CHUNK_SIZE),
  TOTAL_CHUNK_SIZE(TILE_SIZE * CHUNK_SIZE)
{
  for (Tile* tile : tiles)
  {
    this->tiles.push_back(tile);
  }
}

ChunkScript* World::addChunk(const int chunkX, const int chunkY)
{
  ChunkScript* chunk = new ChunkScript(this, chunkX, chunkY);
  addComponent(chunk);
  chunks.push_back(chunk);
  return chunk;
}

void World::gen()
{
  float halfTile = (float)(TILE_SIZE / 2);

  for (uint y = 0; y < CHUNK_SIZE; y++)
  {
    for (uint x = 0; x < CHUNK_SIZE; x++)
    {
      uint tileID = chunks[0]->table[y][x];
      if (tileID > 0)
      {
        addCollision(
          new oak::CollisionRect(
            chunks[0]->WORLD_OFFSET_X + (float)(x * TILE_SIZE) + halfTile,
            chunks[0]->WORLD_OFFSET_Y - (float)(y * TILE_SIZE) - halfTile,
            (float)TILE_SIZE,
            (float)TILE_SIZE
          )
        );
      }
    }
  }
}

void World::addTile(Tile* tile)
{
  tiles.push_back(tile);
}

Tile* World::getTileByID(const uint tileID)
{
  for (Tile* tile : tiles)
  {
    if (tile->tileID == tileID)
    {
      return tile;
    }
  }
  return nullptr;
}

World::~World()
{

}
