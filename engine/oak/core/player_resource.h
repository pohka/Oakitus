#ifndef PLAYER_RESOURCE_H
#define PLAYER_RESOURCE_H

#include "player.h"
#include <oak/core/types.h>

namespace oak
{
  ///<summary>Accessing and management of Players</summary>
  class PlayerResource
  {
    const static uint MAX_PLAYER_COUNT = 4; ///<summary>Maximum number of players in the game</summary>
    static Player* players[MAX_PLAYER_COUNT]; ///<summary>Array of players in the game</summary>
    static uint playerCount; ///<summary>Current player count</summary>
    static uint localPlayerID;

    static Player defaultPlayer;

    public :
      ///<summary>Add a Player</summary>
      static void addPlayer(Player* player);

      ///<summary>Get a Player by ID</summary>
      static Player* getPlayer(uint playerID);

      ///<summary>Get a Player by index</summary>
      static Player* getPlayerByIndex(uint index);

      static Player* getLocalPlayer();

      ///<summary>Execute all Players input Commands</summary>
      static void executeAllCommands();

      static bool isLocalPlayerID(uint playerID);
  };
}


#endif