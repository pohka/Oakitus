#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"
#include <string>

namespace oak
{
  class Texture
  {
    uint id;
    int width;
    int height;
    std::string src;

    public:
      Texture(std::string path, std::string src);
      ~Texture();
      int getHeight() const;
      uint getID() const;
      int getWidth() const;
      std::string getSrc() const;

  };
}

#endif
