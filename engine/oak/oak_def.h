#pragma once
#ifndef OAK_DEF_H
#define OAK_DEF_H

#include "core/types.h"

namespace oak
{
  //direction of an animation
  enum class AnimDirection : uchar
  {
    RIGHT = 0,
    LEFT = 1
  };
}

//entity groups
cnum ENTITY_GROUP_NONE = 0;
cnum ENTITY_GROUP_ACTOR = 1;
cnum ENTITY_GROUP_WORLD = 2;

cnum ANIM_NULL = 0;
cnum ANIM_IDLE = 1;
cnum ANIM_RUN = 2;
cnum ANIM_DEATH = 3;


#endif