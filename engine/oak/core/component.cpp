#include "component.h"

using namespace oak;

Component::Component(uchar tickGroup)
{
  this->tickGroup = tickGroup;
}

uchar Component::getTickGroup() const
{
  return tickGroup;
}


uint Component::getComponentID() const
{
  return componentID;
}

Component::~Component() {}

void Component::onCreate() {}

void Component::onTick() {}

void Component::onDraw() const {}

void Component::onDebugDraw() const {}

void Component::onCollisionHit(Entity& hit) {}
