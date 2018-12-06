#include "player.h"
#include "commands/movement.h"
#include "commands/cast_abiltiys.h"
#include <debug.h>

using namespace game;
using namespace oak;

Player::Player()
{
  assignedUnit = nullptr;

  command::Movement* moveCmd = new command::Movement(*this);
  addCommand(*moveCmd);
  command::CastAbilitys* abilityCastCmd = new command::CastAbilitys(*this);
  addCommand(*abilityCastCmd);
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

Unit* Player::getAssignedUnit() const
{
  if (assignedUnit == nullptr)
  {
    LOG_WARNING << "PLayer doesn't have an assigned unit, playerID:" << this->getID();
  }
  return assignedUnit;
}