#include "Entity.h"
#include "Oakitus.h"

using namespace oak;

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

unsigned int Entity::getID()
{
  return this->entityID;
}

void Entity::onDestroy()
{

}


void Entity::onDraw()
{
  for (unsigned int i = 0; i < components.size(); i++) 
  {
    components[i]->onDraw();
  }
}

void Entity::onUpdate()
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    components[i]->onUpdate();
  }

  for (unsigned int i = 0; i < scripts.size(); i++)
  {
    scripts[i]->onUpdate();
  }
}
