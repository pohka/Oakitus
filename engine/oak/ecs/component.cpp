#include "component.h"
#include <oak/debug.h>

using namespace oak;

Component::Component(
  Reflect reflectID,
  TickGroup tickGroup,
  TickType tickType,
  const bool isEverRendered
) : _REFLECT_ID(reflectID)
{
  this->tickGroup = tickGroup;
  this->tickType = tickType;
  this->isEverRendered = isEverRendered;
  this->isRenderable = isEverRendered;
}

Component::TickGroup Component::getTickGroup() const
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
  switch (tickType)
  {
    case TickType::NOT_TICKABLE :   res = false;            break;
    case TickType::TICKABLE :       res = true;             break;
    case TickType::INTERVAL_TICK:   res = ticker.onTick();  break;
  }


  return res;
}

bool Component::isTickable() const
{
  return (tickType != TickType::NOT_TICKABLE);
}

bool Component::isUsingIntervalTicking() const
{
  return (tickType == TickType::INTERVAL_TICK);
}

float Component::getTickingInterval() const
{
  return ticker.interval;
}

Entity* Component::getOwnerEntity()
{
  return entity;
}