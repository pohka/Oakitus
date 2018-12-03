#ifndef COMMAND_H
#define COMMAND_H

#include <core/input.h>
#include <core/base_player.h>

namespace oak
{
  class BasePlayer;

  ///<summary>Input Command</summary>
  class Command
  {
    public:
      ///<summary>Called once each frame before the update stage</summary>
      virtual void execute() = 0;
  };
}

#endif