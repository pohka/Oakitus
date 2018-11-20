#ifndef TILE_H
#define TILE_H

#include <string>
#include "oak/core/types.h"

namespace game
{
  struct Tile
  {
    enum Collision {
      NONE = 0,
      BOX = 1,
      TOP_LEFT = 2,
      TOP_RIGHT = 3,
      BOTTOM_RIGHT = 4,
      BOTTOM_LEFT = 5
    };

    int id;
    std::string src;
    int srcY;
    int srcX;
    Collision collision;
  };
}
#endif