#include "Entity.h"
#include "Oakitus.h"



Entity::Entity() 
{
	idGen = new IDGenerator();
	this->entityID = idGen->nextID();
	this->position = new Vector3(0, 0, 0);
	Oakitus::addEntity(*this);
}

Entity::~Entity() 
{
	idGen->~IDGenerator();
	for (Component* c : components)
	{
		delete c;
	}
}

void Entity::update()
{

}

void Entity::draw()
{
	for (unsigned int i = 0; i < components.size(); i++) 
	{
		components[i]->draw();
	}
}

void Entity::addComponent(Component& component)
{
	component.entity = this;
	this->components.push_back(&component);
}

unsigned int Entity::getID()
{
	return this->entityID;
}

