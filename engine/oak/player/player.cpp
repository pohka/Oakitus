#include "player.h"
#include <oak/time/time.h>
#include <oak/ecs/id_generator.h>

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


void Player::assignActor(Actor* actor)
{
  actor->owner = this;
  this->assignedActor = actor;
}

void Player::unAssignActor()
{
  if (this->assignedActor != nullptr)
  {
    this->assignedActor->owner = nullptr;
    this->assignedActor = nullptr;
  }
}

Actor* Player::getAssignedActor()
{
  return assignedActor;
}


void Player::removeCommand(const ushort commandID)
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

bool Player::hasCommand(const ushort commandID) const
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