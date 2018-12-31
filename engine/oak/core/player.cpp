#include "player.h"

using namespace oak;

IDGenerator Player::idGen;
std::vector<Command> commands;


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
  for (uint i = 0; i < commands.size(); i++)
  {
    commands[i]->execute();
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
