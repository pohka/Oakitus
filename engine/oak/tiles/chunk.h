#ifndef CHUNK_H
#define CHUNK_H

#include <oak/ecs/entity.h>

namespace tile
{
  class World;

  class Chunk : public oak::Entity
  {
  public:

    //position in chunk coordinates
    const int CHUNK_X;
    const int CHUNK_Y;

    Chunk(const int x, const int y, const World* world);

    void genCollision();

    std::vector<std::vector<uint>> table;

    World* getWorld();
      

  };
}

#endif