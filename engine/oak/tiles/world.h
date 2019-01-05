#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include <oak/ecs/entity.h>
#include <vector>
#include <oak/tiles/tile.h>
#include <oak/collision/base_collision_shape.h>

namespace tile
{
  struct ChunkScript;

  struct World : public oak::Entity
  {
    const uint CHUNK_SIZE;
    const uint TILE_SIZE;

    World(
      const uint TILE_SIZE,
      const uint CHUNK_SIZE
    );
    ~World();

    ChunkScript* addChunk();

    void addTile(Tile* tile);

    Tile* getTileByID(const uint tileID);
    
    void gen();

  private:
    std::vector<ChunkScript*> chunks;
    std::vector<Tile*> tiles;
  };
}

#endif