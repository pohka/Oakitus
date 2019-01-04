#ifndef TILE_CHUNK_H
#define TILE_CHUNK_H

#include <oak/core/types.h>
#include <vector>
#include <oak/ecs/component.h>

namespace tile
{
  struct World;

  struct Chunk : public oak::Component
  {
    friend struct World;

    Chunk(const uint CHUNK_SIZE);
    ~Chunk();

    void onRender() const override;

    std::vector<std::vector<uint>> table;

    private:
      World* world;
      
  };
}

#endif