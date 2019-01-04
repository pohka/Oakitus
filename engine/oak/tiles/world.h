#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <oak/ecs/entity.h>
#include <vector>
#include <oak/tiles/chunk.h>
#include <oak/tiles/tile.h>

namespace tile
{
  struct World : public oak::Entity
  {
    const uint CHUNK_SIZE;
    const uint TILE_SIZE;

    World(
      const uint TILE_SIZE,
      const uint CHUNK_SIZE
    );
    ~World();

    Chunk* addChunk();
    void addTile(Tile* tile);

    Tile* getTileByID(const uint tileID);

  private:
    std::vector<Chunk*> chunks;
    std::vector<Tile*> tiles;
  };
}

#endif