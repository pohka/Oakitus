#include "modifier.h"
#include <core/time.h>

using namespace game;

void Modifier::addProperty(uchar propertyID, int value)
{
  properties.insert(std::pair<uchar, int>(propertyID, value));
}

uint Modifier::getModifierID()
{
  return modifierID;
}

void Modifier::refresh()
{
  if (!isPassive)
  {
    startTime = oak::Time::getTimeNow();
    endTime = startTime + duration;
  }
}