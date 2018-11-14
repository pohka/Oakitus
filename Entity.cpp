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
	for (Script* s : scripts)
	{
		delete s;
	}
}

void Entity::onUpdate()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->update();
	}

	for (unsigned int i = 0; i < scripts.size(); i++)
	{
		scripts[i]->update(this);
	}
}

void Entity::onDraw()
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

void Entity::addScript(Script& script)
{
	script.entity = this;
	this->scripts.push_back(&script);
}

unsigned int Entity::getID()
{
	return this->entityID;
}

void Entity::onDestory()
{

}