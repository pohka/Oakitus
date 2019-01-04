#ifndef MOVEMENT_CMD_H
#define MOVEMENT_CMD_H

#include <oak/oak.h>

namespace sample
{
  struct MovementCMD : oak::Command
  {
    MovementCMD();
    void execute() override;
  };
}

#endif