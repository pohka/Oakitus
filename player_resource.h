#ifndef PLAYER_RESOURCE_H
#define PLAYER_RESOURCE_H

#include "player.h"
#include <core/types.h>

namespace game
{
  class PlayerResource
  {
    const static uint MAX_PLAYER_COUNT = 4;
    static Player* players[MAX_PLAYER_COUNT];
    static uint playerCount;

    public :
      static Player* addPlayer();
      static Player* getPlayer(uint playerID);
      static Player* getPlayerByIndex(uint index);
  };

  //Player* PlayerResource::players[4];
}


#endif