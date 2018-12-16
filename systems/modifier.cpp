#include "modifier.h"
#include <core/time.h>

using namespace game;

Modifier::Modifier(ushort id)
{
  modifierID = id;
  startTime = oak::Time::getTimeNow();
}

void Modifier::init(Unit* owner, uint attackerID)
{
  this->owner = owner;
  this->attackerID = attackerID;
  endTime = startTime + duration;
}

void Modifier::setProp(uchar propertyID, int value)
{
  props.insert(std::pair<uchar, int>(propertyID, value));
}

uint Modifier::getModifierID()
{
  return modifierID;
}

void Modifier::refresh()
{
  if (destroyOnExpire)
  {
    startTime = oak::Time::getTimeNow();
    endTime = startTime + duration;
    onRefresh();
  }
}

float Modifier::getEndTime()
{
  return endTime;
}

void Modifier::onUpdate()
{
  //add ticking here
}

