#ifndef TILE_H
#define TILE_H

#include <string>
#include "oak/core/types.h"

namespace game
{
  class Tile
  {
    unsigned int VAO;
    unsigned int VBO;

    public:
      const int TILE_SIZE = 16;
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
      int textureID;
      int shaderID;
      int y;
      int x;
      Collision collision;
      

      Tile(int x, int y, std::string src, Collision collision, int id);
      ~Tile();
      void onDraw(float x, float y);

  };
}
#endif