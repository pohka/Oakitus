#ifndef TEXTURE_H
#define TEXTURE_H

#include "Types.h"

namespace oak
{
  class Texture
  {
    uint id;
    int width, height;

    public:
      Texture(const char* src);
      ~Texture();
      int getHeight();
      uint getID();
      int getWidth();


  };
}

#endif
