#include "modifier.h"
#include <core/time.h>

using namespace game;

Modifier::Modifier(ModifierData& data)
{
  this->modifierID = data.modifierID;
  this->duration = data.duration;
  this->isPassive = data.isPassive;
  this->isHidden = data.isHidden;
  this->isDebuff = data.isDebuff;
  this->isStackable = data.isStackable;
  this->maxStacks = data.maxStacks;
  stackCount = 1;

  startTime = oak::Time::getTimeNow();
  if (!data.isPassive)
  {
    endTime = startTime + data.duration;
  }

  for (auto it = data.properties.begin(); it != data.properties.end(); ++it)
  {
    properties.insert(std::pair<uchar, int>(it->first, it->second));
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

bool Modifier::getIsDebuff()
{
  return isDebuff;
}