#ifndef PLATFORMER_CONSTANTS_H
#define PLATFORMER_CONSTANTS_H

#include <oak/core/types.h>

namespace plat
{

  cnum ANIM_ACT_IDLE = 0;
  cnum ANIM_ACT_RUN = 1;

  cnum ANIM_PRIORITY_LOWEST = 0;
  cnum ANIM_PRIORITY_HIGH = 1;

  snum COMMAND_MOVEMENT = 1;

  cnum MOVE_STATE_FALLING = 0;
  cnum MOVE_STATE_ON_GROUND = 1;
  cnum MOVE_STATE_JUMPING = 1;
}

#endif
