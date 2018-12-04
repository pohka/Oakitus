#ifndef FALLBACK_H
#define FALLBACK_H

#include "core/shader.h"
#include "core/texture.h"

namespace oak
{
  struct Fallback
  {
    //default resouces
    static Shader shader;
    static Texture texture;

    static void init();
  };
}

#endif