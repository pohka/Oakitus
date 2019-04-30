#pragma once
#ifndef PLAYER_RESOURCE_H
#define PLAYER_RESOURCE_H

#include "player.h"
#include <oak/core/types.h>
#include <vector>

namespace oak
{
  //Accessing and management of Players
  class PlayerResource
  {
    static std::vector<Player*> players;
    static uint playerCount; //Current player count
    static uint localPlayerID;


    public :
      //Add a Player
      static void addPlayer(Player* player);

      //Get a Player by ID
      static Player* getPlayer(uint playerID);

      static Player* getLocalPlayer();

      //Execute all Players input Commands
      static void tickAllCommands();

      static bool isLocalPlayerID(uint playerID);

      static Player* getLocalPlayerBySlot(uint slotIndex);
  };
}


#endif