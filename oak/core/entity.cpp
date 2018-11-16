#include "entity.h"
#include "oakitus.h"

using namespace oak;


Entity::Entity() 
{
  idGen = new IDGenerator();
  this->entityID = idGen->nextID();
  this->position = glm::vec3(0, 0, 0);
  layerID = 0;
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

void Entity::destroy()
{
  Oakitus::destroyEntityByID(this->getID());
}

uint Entity::getID()
{
  return this->entityID;
}

void Entity::onDestroy()
{

}


void Entity::onDraw()
{
  for (uint i = 0; i < components.size(); i++) 
  {
    components[i]->onDraw();
  }
}

void Entity::onUpdate()
{
  for (uint i = 0; i < components.size(); i++)
  {
    components[i]->onUpdate();
  }

  for (uint i = 0; i < scripts.size(); i++)
  {
    scripts[i]->onUpdate();
  }
}
