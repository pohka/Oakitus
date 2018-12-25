#include "base_player.h"

using namespace oak;

IDGenerator BasePlayer::idGen = IDGenerator();
std::vector<Command> commands;


BasePlayer::BasePlayer()
{
  playerID = idGen.nextID();
 
}

BasePlayer::~BasePlayer()
{

}

uint BasePlayer::getPlayerID() const
{
  return playerID;
}

void BasePlayer::executeCommands()
{
  for (uint i = 0; i < commands.size(); i++)
  {
    commands[i]->execute();
  }
}

void BasePlayer::addCommand(Command& command)
{
  commands.push_back(&command);
}
