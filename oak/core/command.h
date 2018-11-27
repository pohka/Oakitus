#ifndef COMMAND_H
#define COMMAND_H

#include <core/input.h>
#include <core/base_player.h>

namespace oak
{
  class BasePlayer;

  class Command
  {
    public:
      virtual void execute() = 0;
  };
}

#endif