#ifndef FALLBACK_H
#define FALLBACK_H

#include "core/shader.h"
#include "core/texture.h"
#include "core/base_player.h"
#include "components/animator.h"
#include "components/sprite_animation.h"

namespace oak
{
  struct Fallback
  {
    //default resouces
    static Shader shader;
    static Texture texture;
    static BasePlayer basePlayer;
    static Animator animator;
    static SpriteAnimation spriteAnim;
    static Entity entity;

    static void init();
    static void update();
    static void draw();
  };
}

#endif