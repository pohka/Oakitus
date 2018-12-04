#include "player_resource.h"
#include "types.h"
#include "../fallback.h"

using namespace oak;

unsigned int PlayerResource::playerCount = 0;
BasePlayer* PlayerResource::players[4];

void PlayerResource::addPlayer(BasePlayer& player)
{

  //if enough player slots
  if (playerCount + 1 < MAX_PLAYER_COUNT)
  {
    PlayerResource::players[playerCount] = &player;
    playerCount++;
  }
  
}

BasePlayer& PlayerResource::getPlayer(uint playerID)
{
  for (uint i = 0; i < MAX_PLAYER_COUNT; i++)
  {
    if (players[i]->getID() == playerID)
    {
      return *players[i];
    }
  }

  return Fallback::basePlayer;
 // return nullptr;
}

BasePlayer& PlayerResource::getPlayerByIndex(uint index)
{
  if (index >= MAX_PLAYER_COUNT || players[index] == nullptr)
  {
    return Fallback::basePlayer;
  }
  return *players[index];
}

void PlayerResource::executeAllCommands()
{
  for (uint i = 0; i < MAX_PLAYER_COUNT; i++)
  {
    if (players[i] != nullptr)
    {
      players[i]->executeCommands();
    }
  }
}