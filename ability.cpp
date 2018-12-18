#include "ability.h"
#include <debug.h>

using namespace game;

oak::IDGenerator Ability::idGen = oak::IDGenerator();

Ability::Ability()
{
  id = idGen.nextID();
  startTime = 0;
  endTime = 0;
}

void Ability::init(Unit* owner)
{
  this->owner = owner;
}

Unit* Ability::getOwner()
{
  return owner;
}

uint Ability::getAbilityID() const
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
  //not enough mana
  if (owner->getMana() < manaCost)
  {
    return;
  }

  float now = oak::Time::getTimeNow();
  startTime = now + preCastTime;
  endTime = startTime + castTime;

  castState = CAST_STATE_PRECAST;
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


uchar Ability::getCastState() const
{
  return castState;
}

uchar Ability::getTargetType() const
{
  return targetType;
}

void Ability::setCastState(uchar state)
{
  castState = state;
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

int Ability::getManaCost()
{
  return manaCost;
}

void Ability::onOwnerDeath()
{
  
}