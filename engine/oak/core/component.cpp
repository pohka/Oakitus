#include "component.h"

using namespace oak;

Component::Component(uchar tickGroup, bool isEverRendered)
{
  this->tickGroup = tickGroup;
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
