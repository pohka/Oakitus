#include "Component.h"

using namespace oak;

uint componentCount = 0;


Component::Component()
{
  this->componentID = Component::getNextID();
}

Component::~Component() {}

uint Component::getNextID()
{
  componentCount++;
  return componentCount;
}

void Component::onUpdate() {}

void Component::onDraw(){}

