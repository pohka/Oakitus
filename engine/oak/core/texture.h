#ifndef TEXTURE_H
#define TEXTURE_H


#include "types.h"
#include <string>

namespace oak
{
  ///<summary>Texture</summary>
  class Texture
  {
    uint id;
    int width;
    int height;
    std::string src;

    public:
      Texture(std::string src, bool isOnHeap = true);
      ~Texture();
      int getHeight() const;
      uint getID() const;
      int getWidth() const;
      std::string getSrc() const;

      void load();
  };
}

#endif
