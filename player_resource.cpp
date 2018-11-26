#include "player_resource.h"
#include <core/types.h>

using namespace oak;
using namespace game;

unsigned int game::PlayerResource::playerCount = 0;
Player* PlayerResource::players[4];

Player* PlayerResource::addPlayer()
{
  if (playerCount + 1 >= MAX_PLAYER_COUNT)
  {
    //not enough player slots
    return nullptr;
  }

  Player* p = new Player();
  PlayerResource::players[playerCount] = p;
  playerCount++;
  return p;
}

Player* PlayerResource::getPlayer(uint playerID)
{
  for (uint i = 0; i < MAX_PLAYER_COUNT; i++)
  {
    if (players[i]->getID() == playerID)
    {
      return players[i];
    }
  }
  return nullptr;
}

Player* PlayerResource::getPlayerByIndex(uint index)
{
  return players[index];
}