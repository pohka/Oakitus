#include "world.h"

using namespace tile;

World::World(
  const uint TILE_SIZE,
  const uint CHUNK_SIZE
) : 
  TILE_SIZE(TILE_SIZE),
  CHUNK_SIZE(CHUNK_SIZE)
{
  for (Tile* tile : tiles)
  {
    this->tiles.push_back(tile);
  }
}

Chunk* World::addChunk()
{
  Chunk* chunk = new Chunk(CHUNK_SIZE);
  chunk->world = this;
  chunks.push_back(chunk);
  addComponent(chunk);
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