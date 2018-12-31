#ifndef COMMAND_H
#define COMMAND_H

#include <oak/core/input.h>
#include <oak/core/player.h>

namespace oak
{
  class Player;

  ///<summary>Input Command</summary>
  class Command
  {
    public:
      //Command(Player* player)
      //{
      //  this->player = player;
      //}
      friend class Player;

      ///<summary>Called once each frame before the update stage</summary>
      virtual void execute() = 0;

    protected:
      Player* player;
  };
}

#endif