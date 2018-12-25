#include "player.h"
#include "commands/movement.h"
#include "commands/cast_abiltiys.h"
#include <oak/debug.h>

using namespace game;
using namespace oak;

Player::Player()
{

  command::Movement* moveCmd = new command::Movement(*this);
  addCommand(*moveCmd);
  command::CastAbilitys* abilityCastCmd = new command::CastAbilitys(*this);
  addCommand(*abilityCastCmd);
}

Player::~Player()
{
  //if (!hasAssignedUnit)
  //{
  //  //delete assignedUnit;
  //}
}

void Player::setAssignedUnit(Unit& unit)
{
  hasAssignedUnit = true;
  assignedUnitID = unit.getID();
  unit.setOwner(getPlayerID());
}

Unit* Player::getAssignedUnit() const
{
  if (!hasAssignedUnit)
  {
    LOG_WARNING << "PLayer doesn't have an assigned unit, playerID:" << this->getPlayerID();
  }
  Entity* ent = Entity::findEntityByID(assignedUnitID);
  if (ent == nullptr)
  {
    return nullptr;
  }

  return static_cast<Unit*>(Entity::findEntityByID(assignedUnitID));
}