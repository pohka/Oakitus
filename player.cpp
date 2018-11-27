#include "player.h"
#include "commands/movement.h"

using namespace game;
using namespace oak;

Player::Player()
{
  assignedUnit = nullptr;

  command::Movement* moveCmd = new command::Movement(*this);
  addCommand(*moveCmd);
}

Player::~Player()
{
  if (assignedUnit != nullptr)
  {
    delete assignedUnit;
  }
}

void Player::setAssignedUnit(Unit& unit)
{
  assignedUnit = &unit;
}

Unit& Player::getAssignedUnit()
{
  return *assignedUnit;
}