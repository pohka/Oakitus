#include "modifier.h"
#include <core/time.h>

using namespace game;

Modifier::Modifier(float duration, bool isPassive, bool isHidden)
{
  this->duration = duration;
  this->isPassive = isPassive;
  this->isHidden = isHidden;
  startTime = oak::Time::getTimeNow();
  if (!isPassive)
  {
    endTime = startTime + duration;
  }
}

Modifier::~Modifier()
{

}

void Modifier::addProperty(uchar propertyID, int value)
{
  properties.insert(std::pair<uchar, int>(propertyID, value));
}

uint Modifier::getModifierID()
{
  return modifierID;
}

bool Modifier::getIsPassive()
{
  return isPassive;
}

bool Modifier::getIsHidden()
{
  return isHidden;
}