#pragma once
#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <oak/ecs/entity.h>
#include <vector>
#include <oak/tiles/tile.h>
#include "chunk.h"

namespace tile
{
  class World : public oak::Entity
  {
  public:
    const uint CHUNK_SIZE;
    const uint TILE_SIZE;
    const int TOTAL_CHUNK_SIZE;

    World(
      const uint TILE_SIZE,
      const uint CHUNK_SIZE
    );
    ~World();

    Chunk* addChunk(int chunkX, int chunkY);

    void addTile(Tile* tile);

    Tile* getTileByID(uint tileID);

  private:
    std::vector<Tile*> tiles;
  };
}

#endif