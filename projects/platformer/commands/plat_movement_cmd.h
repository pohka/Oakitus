#ifndef PLATFORMER_MOVEMENT_CMD_H
#define PLATFORMER_MOVEMENT_CMD_H

#include <oak/oak.h>

namespace plat
{
  struct MovementCMD : oak::Command
  {
    MovementCMD();
    void execute() override;

    const float gravity = 100.0f;
    const float speed = 300.0f;

    cnum STATE_AIR = 1;
    cnum STATE_GROUND = 2;

    uchar state = STATE_AIR;
  };
}

#endif