#include "world.h"


using namespace tile;

World::World(
  const uint TILE_SIZE,
  const uint CHUNK_SIZE
) : 
  TILE_SIZE(TILE_SIZE),
  CHUNK_SIZE(CHUNK_SIZE),
  TOTAL_CHUNK_SIZE(TILE_SIZE * CHUNK_SIZE),
  Entity(ENTITY_GROUP_WORLD)
{
  for (Tile* tile : tiles)
  {
    this->tiles.push_back(tile);
  }
}

Chunk* World::addChunk(const int chunkX, const int chunkY)
{
  Chunk* chunk = new Chunk(chunkX, chunkY, this);
  addChild(chunk);;
  return chunk;
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
