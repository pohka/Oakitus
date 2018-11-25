#include "entity.h"
#include "store.h"

using namespace oak;

std::vector<Entity*> Entity::entitys;
std::queue<uint> Entity::destroyEntIDQueue;
IDGenerator Entity::entityIDGen = IDGenerator();


Entity::Entity() 
{
  componentIDGen = IDGenerator();
  this->entityID = entityIDGen.nextID();
  this->position = glm::vec3(0, 0, 0);
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
}

Entity::~Entity()
{
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
  component.componentID = componentIDGen.nextID();
  this->components.push_back(&component);
}

void Entity::addScript(Script& script)
{
  script.entity = this;
  this->scripts.push_back(&script);
}

void Entity::destroy()
{
  destroyEntityByID(this->getID());
}

uint Entity::getID()
{
  return this->entityID;
}

std::string Entity::getName()
{
  return name;
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


//static functions
//----------------------------

void Entity::addEntity(Entity& entity)
{
  entitys.push_back(&entity);
}

void Entity::deleteAllEntitys()
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    Entity* tmp = entitys[i];
    entitys.erase(entitys.begin() + i); //remove from vector
    i--;
    delete tmp;
  }
}

void Entity::destroyEntityByID(uint entityID)
{
  destroyEntIDQueue.push(entityID);
}

Entity* Entity::findEntityByID(uint id)
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->getID() == id)
    {
      return entitys[i];
    }
  }

  return nullptr;
}

Entity* Entity::findEntityByName(std::string name)
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->name.compare(name) == 0)
    {
      return entitys[i];
    }
  }

  return nullptr;
}

std::vector<Entity*> Entity::getGlobalEntitys()
{
  std::vector<Entity*> list;
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->isGlobal)
    {
      list.push_back(entitys[i]);
    }
  }
  return list;
}