#ifndef COLLISION_LAYER_H
#define COLLISION_LAYER_H

#include <oak/core/types.h>
#include <limits>

namespace oak
{
  //bitwise
  const uint COLLISION_LAYER_ALL = std::numeric_limits<unsigned int>().max();
  const uint COLLISION_LAYER_DEFAULT = 1;
  const uint COLLISION_LAYER_WORLD = 2;
  const uint COLLISION_LAYER_PLAYER = 4;
  const uint COLLISION_LAYER_ENEMY = 8;
}

#endif