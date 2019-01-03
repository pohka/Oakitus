#ifndef PLAYER_RESOURCE_H
#define PLAYER_RESOURCE_H

#include "player.h"
#include <oak/core/types.h>
#include <vector>

namespace oak
{
  ///<summary>Accessing and management of Players</summary>
  class PlayerResource
  {
    static std::vector<Player*> players;
    static uint playerCount; ///<summary>Current player count</summary>
    static uint localPlayerID;

    public :
      ///<summary>Add a Player</summary>
      static void addPlayer(Player* player);

      ///<summary>Get a Player by ID</summary>
      static Player* getPlayer(uint playerID);

      static Player* getLocalPlayer();

      ///<summary>Execute all Players input Commands</summary>
      static void executeAllCommands();

      static bool isLocalPlayerID(uint playerID);
  };
}


#endif