#include "player_resource.h"
#include <oak/core/types.h>
#include <oak/debug.h>

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

void PlayerResource::executeAllCommands()
{
  for (Player* player : players)
  {
    player->executeCommands();
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