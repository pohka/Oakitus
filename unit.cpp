#include "unit.h"
#include <debug.h>

using namespace game;

const float Unit::BASE_MOVE_SPEED = 400.0f;

Unit::Unit()
{
  Player* owner = nullptr;
  moveSpeed = BASE_MOVE_SPEED;
}

Unit::~Unit()
{
  owner = nullptr;
  while (!abilitys.empty())
  {
    delete abilitys[0];
    abilitys.erase(abilitys.begin());
  }
  LOG << "deallocated unit: " << name;
}

Player* Unit::getOwner() const
{
  return owner;
}


bool Unit::hasOwner() const
{
  return (owner != nullptr);
}

float Unit::getMoveSpeed() const
{
  return moveSpeed;
}

void Unit::setMoveSpeed(float moveSpeed)
{
  this->moveSpeed = moveSpeed;
}

void Unit::addAbility(Ability& ability)
{
  ability.caster = this;
  abilitys.push_back(&ability);
}

Ability* Unit::getAbilityByIndex(uint index) const
{
  if (index >= abilitys.size())
  {
    return nullptr;
  }
  return abilitys[index];
}