#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include <oak/input/input.h>
#include <oak/player/player.h>

namespace oak
{
  class Player;

  //Input Command
  class Command
  {
    public:
      Command(const unsigned short commandID) : commandID(commandID) {};
      //Command(Player* player)
      //{
      //  this->player = player;
      //}
      friend class Player;

      //Called once each frame before the update stage
      virtual void onTick() = 0;

      const unsigned short commandID;

    protected:
      Player* player;
      bool canExecuteWhenPaused = false;
  };
}

#endif