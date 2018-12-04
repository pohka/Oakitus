#ifndef FALLBACK_H
#define FALLBACK_H

#include "core/shader.h"
#include "core/texture.h"
#include "core/base_player.h"


namespace oak
{
  struct Fallback
  {
    //default resouces
    static Shader shader;
    static Texture texture;
    static BasePlayer basePlayer;


    static void init();
  };
}

#endif