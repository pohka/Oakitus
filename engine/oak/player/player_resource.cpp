#include "player_resource.h"
#include <oak/core/types.h>

using namespace oak;

unsigned int PlayerResource::playerCount = 0;
std::vector<Player*> PlayerResource::players;
uint PlayerResource::localPlayerID = 0;

void PlayerResource::addPlayer(Player* player)
{
  players.push_back(player);
}

Player* PlayerResource::getPlayer(uint playerID)
{
  for (Player* player : players)
  {
    if (player->getPlayerID())
    {
      return player;
    }
  }
  return nullptr;
}

void PlayerResource::tickAllCommands()
{
  for (Player* player : players)
  {
    player->tickCommands();
  }
}

bool PlayerResource::isLocalPlayerID(uint id)
{
  //for future multiplayer feature
  return true;
}

Player* PlayerResource::getLocalPlayer()
{
  //for future multiplayer feature
  return players[localPlayerID];
}

Player* PlayerResource::getLocalPlayerBySlot(uint slotIndex)
{
  unsigned int slotCount = 0;
  for (Player* player : players)
  {
    if (isLocalPlayerID(player->getPlayerID()))
    {
      slotCount++;
      if (slotCount == slotIndex)
      {
        return player;
      }
    }
  }
  return nullptr;
}