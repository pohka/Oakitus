#include "player.h"
#include "time.h"

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

void Player::executeCommands()
{
  bool isPaused = Time::getIsPaused();
  for (Command* command : commands)
  {
    if (!isPaused || (isPaused && command->canExecuteWhenPaused))
    {
      command->execute();
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
