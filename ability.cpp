#include "ability.h"
#include <debug.h>

using namespace game;

oak::IDGenerator Ability::idGen = oak::IDGenerator();

Ability::Ability()
{
 // LOG << "ability contrustcor";
  id = idGen.nextID();
  startTime = 0;
  endTime = 0;
  //CastingState castingState = CastingState::NONE;
  //TargetType targetType = TargetType::NO_TARGET;
}

uint Ability::getID() const
{
  return id;
}


void Ability::castOnTarget(Unit& unit)
{
  target.targetEntityID = unit.getID();
  beginCasting();
}

void Ability::castOnPoint(glm::vec2 point)
{
  target.point = point;
  beginCasting();
}

void Ability::castNoTarget()
{
  beginCasting();
}

void Ability::beginCasting()
{
  float now = oak::Time::getTimeNow();
  startTime = now + preCastTime;
  endTime = startTime + castTime;

  castingState = CastingState::PRECAST;
  onCast();
}

float Ability::getStartTime() const
{
  return startTime;
}
float Ability::getEndTime() const
{
  return endTime;
}


CastingState Ability::getCastingState() const
{
  return castingState;
}

TargetType Ability::getTargetType() const
{
  return targetType;
}

void Ability::setCastingState(CastingState state)
{
  castingState = state;
}

//when casting was successfully requested
void Ability::onCast() 
{
} 

//when the precast ends
void Ability::onAbilityStart() 
{
} 

//when the cast time ends
void Ability::onAbilityEnd() 
{
} 