#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include <oak/input/input.h>
#include <oak/player/player.h>

namespace oak
{
  class Player;

  ///<summary>Input Command</summary>
  class Command
  {
    public:
      Command(const unsigned short commandID) : commandID(commandID) {};
      //Command(Player* player)
      //{
      //  this->player = player;
      //}
      friend class Player;

      ///<summary>Called once each frame before the update stage</summary>
      virtual void onTick() = 0;

      const unsigned short commandID;

    protected:
      Player* player;
      bool canExecuteWhenPaused = false;
  };
}

#endif