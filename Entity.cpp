#include "Entity.h"
#include "shader_s.h"

unsigned int entityCount = 0;

Entity::Entity() 
{
	this->entityID = Entity::getNextID();
	this->position = new Vector3(0, 0, 0);
}

Entity::~Entity() 
{

}

unsigned int Entity::getNextID()
{
	entityCount++;
	return entityCount;
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