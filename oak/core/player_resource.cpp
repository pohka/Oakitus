#include "player_resource.h"
#include "types.h"
#include "../fallback.h"
#include <debug.h>

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
  else
  {
    LOG_WARNING << "Player not added because the max player count has been reached";
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

  LOG_WARNING << "FALLBACK | BasePlayer not found with ID: " << playerID;
  return Fallback::basePlayer;
}

BasePlayer& PlayerResource::getPlayerByIndex(uint index)
{
  if (index >= MAX_PLAYER_COUNT || players[index] == nullptr)
  {
    LOG_WARNING << "FALLBACK | BasePlayer not found at index: " << index;
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