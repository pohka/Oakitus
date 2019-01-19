#include "component.h"
#include <oak/debug.h>

using namespace oak;

Component::Component(const uint REFLECT_ID, cnum tickGroup, cnum tickingType, const bool isEverRendered) : _REFLECT_ID(REFLECT_ID)
{
  this->tickGroup = tickGroup;
  this->tickingType = tickingType;
  this->isEverRendered = isEverRendered;
  this->isRenderable = isEverRendered;
}

uchar Component::getTickGroup() const
{
  return tickGroup;
}


uint Component::getComponentID() const
{
  return componentID;
}

bool Component::getIsRenderable() const
{
  return isRenderable;
}

Component::~Component() {}

void Component::onCreate() {}

void Component::onTick() {}

void Component::onRender() const {}

void Component::onDebugDraw() const {}


void Component::onDestroy() {}

void Component::onCollisionHit(Entity& hit) {}

bool Component::canTickThisFrame()
{
  bool res = false;
  switch (tickingType)
  {
    case TICK_TYPE_NOT_TICKABLE :   res = false;            break;
    case TICK_TYPE_TICKABLE :       res = true;             break;
    case TICK_TYPE_INTERVAL_TICK:   res = ticker.onTick();  break;
  }


  return res;
}

bool Component::isTickable() const
{
  return (tickingType != TICK_TYPE_NOT_TICKABLE);
}

bool Component::isUsingIntervalTicking() const
{
  return (tickingType == TICK_TYPE_INTERVAL_TICK);
}

float Component::getTickingInterval() const
{
  return ticker.interval;
}