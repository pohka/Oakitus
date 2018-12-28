#include "component.h"

using namespace oak;

Component::Component() 
{
  
}

Component::~Component() {}

void Component::onCreate() {}

void Component::onTick() {}

void Component::onLateTick() {}

void Component::onDraw() const {}

void Component::onDebugDraw() const {}

void Component::onCollisionHit(Entity& hit) {}
