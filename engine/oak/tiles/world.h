#pragma once
#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <oak/ecs/entity.h>
#include <vector>
#include <oak/tiles/tile.h>
#include <oak/collision/base_collision_shape.h>
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

    Chunk* addChunk(const int chunkX, const int chunkY);

    void addTile(Tile* tile);

    Tile* getTileByID(const uint tileID);

  private:
    std::vector<Tile*> tiles;
  };
}

#endif