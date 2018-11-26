#ifndef PLAYER_RESOURCE_H
#define PLAYER_RESOURCE_H

#include "base_player.h"
#include <core/types.h>

namespace oak
{
  class PlayerResource
  {
    const static uint MAX_PLAYER_COUNT = 4;
    static BasePlayer* players[MAX_PLAYER_COUNT];
    static uint playerCount;

    public :
      static void addPlayer(BasePlayer& player);
      static BasePlayer* getPlayer(uint playerID);
      static BasePlayer* getPlayerByIndex(uint index);
  };

  //Player* PlayerResource::players[4];
}


#endif