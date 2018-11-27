#include "unit.h"

using namespace game;

const float Unit::BASE_MOVE_SPEED = 400.0f;

Unit::Unit()
{
  Player* owner = nullptr;
  moveSpeed = BASE_MOVE_SPEED;
}

Unit::~Unit()
{

}

Player* Unit::getOwner()
{
  return owner;
}


bool Unit::hasOwner()
{
  return (owner != nullptr);
}

float Unit::getMoveSpeed()
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

Ability* Unit::getAbilityByIndex(uint index)
{
  if (index >= abilitys.size())
  {
    return nullptr;
  }
  return abilitys[index];
}