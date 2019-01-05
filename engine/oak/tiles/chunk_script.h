#ifndef  CHUNK_SCRIPT_H
#define  CHUNK_SCRIPT_H

#include <oak/ecs/component.h>
#include "world.h"

namespace tile
{
  struct ChunkScript : oak::Component
  {
    friend struct World;

    ChunkScript(World* world);

    void onCreate() override;
    void onRender() const override;

    std::vector<std::vector<uint>> table;
    World* world;
  };
}

#endif
