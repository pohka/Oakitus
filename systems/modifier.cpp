#include "modifier.h"
#include <core/time.h>

using namespace game;

Modifier::Modifier(ushort id)
{
  modifierID = id;
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
  if (!isPassive)
  {
    startTime = oak::Time::getTimeNow();
    endTime = startTime + duration;
  }
}