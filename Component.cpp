#include "Component.h"

unsigned int componentCount = 0;


Component::Component()
{
	this->componentID = Component::getNextID();
}

Component::~Component() {}

unsigned int Component::getNextID()
{
	componentCount++;
	return componentCount;
}

void Component::onUpdate() {}

void Component::onDraw(){}

