#include "modifier.h"
#include <core/time.h>
#include "../unit.h"

using namespace game;

Modifier::Modifier(ushort id)
{
  modifierID = id;
  startTime = oak::Time::getTimeNow();
}

void Modifier::init(Unit* owner, uint casterID)
{
  this->owner = owner;
  this->casterID = casterID;
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
  if (
    ticker.isTicking && 
    ticker.nextTickTime <= oak::Time::getTimeNow() && 
    ticker.nextTickTime < endTime
  )
  {
    onIntervalTick();
    ticker.nextTickTime += ticker.interval;
  }
}

void Modifier::startTicker(float interval)
{
  ticker.isTicking = true;
  ticker.interval = interval;
  ticker.nextTickTime = interval + oak::Time::getTimeNow();
}

void Modifier::onIntervalTick()
{

}

void Modifier::destroy()
{
  onDestroy();
  owner->removeModifier(modifierID, casterID);
}