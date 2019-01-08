#ifndef COLLISION_LAYER_H
#define COLLISION_LAYER_H

#include <oak/core/types.h>

namespace oak
{
  //bitwise
  const uint COLLISION_LAYER_DEFAULT = 0;
  const uint COLLISION_LAYER_WORLD = 1;
  const uint COLLISION_LAYER_PLAYER = 2;
  const uint COLLISION_LAYER_ENEMY = 4;
}

#endif