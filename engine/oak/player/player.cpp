#include "player.h"
#include <oak/time/time.h>
#include <oak/ecs/id_generator.h>
#include <lua/lua.hpp>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_scene.h>
#include <oak/debug.h>

using namespace oak;

IDGenerator Player::idGen;


Player::Player()
{
  playerID = idGen.nextID();
}

Player::~Player()
{

}

uint Player::getPlayerID() const
{
  return playerID;
}

void Player::tickCommands()
{
  bool isPaused = Time::getIsPaused();
  for (Command* command : commands)
  {
    if (!isPaused || (isPaused && command->canExecuteWhenPaused))
    {
      command->onTick();
    }
  }
}

void Player::addCommand(Command* command)
{
  command->player = this;
  commands.push_back(command);
}

void Player::assignEntity(Entity* entity)
{
  this->assignedEntity = entity;
}

void Player::unassignEntity()
{
  assignedEntity = nullptr;
}

Entity* Player::getAssignedEntity()
{
  return assignedEntity;
}


void Player::removeCommand(ushort commandID)
{
  for (unsigned int i=0; i<commands.size(); i++)
  {
    if (commands[i]->commandID == commandID)
    {
      delete commands[i];
      commands.erase(commands.begin() + i);
      return;
    }
  }
}

bool Player::hasCommand(ushort commandID) const
{
  for (unsigned int i = 0; i < commands.size(); i++)
  {
    if (commands[i]->commandID == commandID)
    {
      return true;
    }
  }
  return false;
}