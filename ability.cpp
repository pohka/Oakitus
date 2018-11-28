#include "ability.h"

using namespace game;


void Ability::castOnTarget(Unit& unit)
{
  target.targetEntityID = unit.getID();
  onCast();
}

void Ability::castOnPoint(glm::vec2 point)
{
  target.point = point;
  onCast();
}

void Ability::castNoTarget()
{
  onCast();
}


CastingState Ability::getCastingState() const
{
  return castingState;
}

TargetType Ability::getTargetType() const
{
  return targetType;
}

void Ability::onCast() {} //when casting was successfully requested
void Ability::onAbilityStart() {} //when the precast ends
void Ability::onAbilityEnd() {} //when the cast time ends