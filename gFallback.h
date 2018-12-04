#ifndef GFALLBACK_H
#define GFALLBACK_H

#include "unit.h"
#include "player.h"
#include <components/animator.h>
#include <components/sprite_animation.h>
#include "components/animator.h"

namespace game
{
  
  struct gFallback
  {
    static Player player;
    static Unit unit;

    static oak::Entity entity;
    static oak::Animator animator;
    static oak::SpriteAnimation spriteAnim;
    
    static void init();
  };
}

#endif