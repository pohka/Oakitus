#ifndef TEXTURE_H
#define TEXTURE_H


#include <oak/core/types.h>
#include "asset.h"

namespace oak
{

  ///<summary>Texture</summary>
  class Texture : public Asset
  {
    int width;
    int height;

    public:
      Texture(std::string src, bool isEngineAsset);
      ~Texture();
      int getHeight() const;
      int getWidth() const;

      void load();
  };
}

#endif
