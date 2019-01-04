#include "chunk.h"
#include "world.h"
#include <oak/debug.h>

using namespace tile;

Chunk::Chunk(const uint CHUNK_SIZE) : Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, true)
{
  table.resize(CHUNK_SIZE);
  for (std::vector<uint>& row : table)
  {
    row.resize(CHUNK_SIZE);
  }
}

Chunk::~Chunk()
{

}

void Chunk::onRender() const
{
  uint tileID;
  for (uint y = 0; y < table.size(); y++)
  {
    for (uint x = 0; x < table[y].size(); x++)
    {
      tileID = table[y][x];
      
      if (tileID != 0)
      {
        Tile* tile = world->getTileByID(tileID);
        if (tile != nullptr)
        {
          LOG << "rendering";
          tile->onRender(
            x * world->TILE_SIZE, 
            y * world->TILE_SIZE
          );
        }
      }
    }
  }
}