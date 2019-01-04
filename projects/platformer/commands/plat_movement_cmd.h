#ifndef PLATFORMER_MOVEMENT_CMD_H
#define PLATFORMER_MOVEMENT_CMD_H

#include <oak/oak.h>

namespace plat
{
  struct MovementCMD : oak::Command
  {
    MovementCMD();
    void execute() override;
  };
}

#endif