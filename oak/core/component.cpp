#include "component.h"

using namespace oak;

Component::Component() 
{
  componentID = 0;
}

Component::~Component() {}

void Component::onStart() {}

void Component::onUpdate() {}

void Component::onDraw() const {}

void Component::onDebugDraw() const {}
