#include "Entity.h"
#include "shader_s.h"
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

}

void Entity::draw(Shader& shader)
{
	for (unsigned int i = 0; i < components.size(); i++) 
	{
		components[i]->draw(this->position->x, this->position->y, this->position->z, shader);
	}
}

void Entity::addComponent(Component& component)
{
	this->components.push_back(&component);
}

unsigned int Entity::getID()
{
	return this->entityID;
}

