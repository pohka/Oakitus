#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"
#include <string>

namespace oak
{
  class Texture
  {
    uint id;
    int width, height;
    std::string src;

    public:
      Texture(std::string path, std::string src);
      ~Texture();
      int getHeight();
      uint getID();
      int getWidth();
      std::string getSrc();

  };
}

#endif
