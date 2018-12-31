#include "player_resource.h"
#include "types.h"
#include <oak/debug.h>

using namespace oak;

unsigned int PlayerResource::playerCount = 0;
Player* PlayerResource::players[MAX_PLAYER_COUNT];
uint localPlayerID = 0;
Player PlayerResource::defaultPlayer = Player();

void PlayerResource::addPlayer(Player* player)
{

  //if enough player slots
  if (playerCount + 1 < MAX_PLAYER_COUNT)
  {
    PlayerResource::players[playerCount] = player;
    playerCount++;
  }
  else
  {
    LOG_WARNING << "Player not added because the max player count has been reached";
  }
  
}

Player* PlayerResource::getPlayer(uint playerID)
{
  for (uint i = 0; i < MAX_PLAYER_COUNT; i++)
  {
    if (players[i]->getPlayerID() == playerID)
    {
      return players[i];
    }
  }

  LOG_WARNING << "FALLBACK | BasePlayer not found with ID: " << playerID;
  return &defaultPlayer;
}

Player* PlayerResource::getPlayerByIndex(uint index)
{
  if (index >= MAX_PLAYER_COUNT || players[index] == nullptr)
  {
    LOG_WARNING << "FALLBACK | BasePlayer not found at index: " << index;
    return &defaultPlayer;
  }
  return players[index];
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

bool PlayerResource::isLocalPlayerID(uint id)
{
  //for future multiplayer feature
  return true;
}

Player* PlayerResource::getLocalPlayer()
{
  //for future multiplayer feature
  return players[0];

  //for future multiplayer feature
  //for (uint i = 0; i < MAX_PLAYER_COUNT; i++)
  //{
  //  if (players[i]->getPlayerID() == localPlayerID)
  //  {
  //    return players[i];
  //  }
  //}
}