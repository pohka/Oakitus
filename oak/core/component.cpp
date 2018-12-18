#include "component.h"

using namespace oak;

Component::Component() 
{
  
}

Component::~Component() {}

void Component::onCreate() {}

void Component::onUpdate() {}

void Component::onLateUpdate() {}

void Component::onDraw() const {}

void Component::onDebugDraw() const {}

void Component::onCollisionHit(Entity& hit) {}
