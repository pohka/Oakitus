#ifndef  CHUNK_SCRIPT_H
#define  CHUNK_SCRIPT_H

#include <oak/ecs/component.h>
#include "world.h"

namespace tile
{
  struct ChunkScript : oak::Component
  {
    friend struct World;

    //chunk offset in viewport coords
    const float VP_OFFSET_X;
    const float VP_OFFSET_Y;

    //chunk offset in world coords
    const float WORLD_OFFSET_X;
    const float WORLD_OFFSET_Y;

    ChunkScript(World* world, const int x, const int y);

    void onCreate() override;
    void onRender() const override;

    std::vector<std::vector<uint>> table;
    World* world;
  };
}

#endif
