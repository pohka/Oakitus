#include "entity.h"
#include "component.h"
#include "../collision/base_collision_shape.h"
#include <debug.h>

using namespace oak;

std::vector<Entity*> Entity::entitys;
std::queue<uint> Entity::queuedDestroyEntityIDs;
IDGenerator Entity::entityIDGen = IDGenerator();
std::queue<Entity*> Entity::pendingEntityInstances;


Entity::Entity(bool isFallback) 
{
  m_isFallback = isFallback;
  //set default values
  componentIDGen = IDGenerator();
  this->entityID = entityIDGen.nextID();
  this->position = glm::vec3(0, 0, 0);
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
  collisionLayer = CollisionLayer::NONE;
}

Entity::~Entity()
{
  if (!m_isFallback)
  {
    for (Component* c : components)
    {
      delete c;
    }
  }
}

void Entity::addComponent(Component* component)
{
  //give the component a unique ID and tell it who its owner entity is
  component->entity = this;
  component->componentID = componentIDGen.nextID();
  this->components.push_back(component);
}

void Entity::addCollision(BaseCollisionShape* shape)
{
  shape->entity = this;
  collisionShapes.push_back(shape);
}

void Entity::addRigidBody(BaseRigidBody* rigidBody)
{
  rigidBody->entity = this;
  this->rigidBody = rigidBody;
  this->components.push_back(rigidBody);
}

void Entity::instantiate()
{
  Entity::pendingEntityInstances.push(this);
}

void oak::Entity::instantiate(float x, float y)
{
  this->position.x = x;
  this->position.y = y;
  Entity::pendingEntityInstances.push(this);
}

void Entity::destroy()
{
  Entity::queuedDestroyEntityIDs.push(entityID);
}

void Entity::destroyEntityByID(uint id)
{
  Entity::queuedDestroyEntityIDs.push(id);
}

uint Entity::getID() const
{
  return this->entityID;
}

CollisionLayer Entity::getCollisionLayer() const
{
  return collisionLayer;
}

std::string Entity::getName() const
{
  return name;
}

void Entity::onStart()
{
  for (Component* comp : components)
  {
    comp->onStart();
  }
}

void Entity::onDestroy()
{
  
}

void Entity::onDraw() const
{
  for (uint i = 0; i < components.size(); i++) 
  {
    components[i]->onDraw();
  }
}

void Entity::onDebugDraw() const
{
  for(Component* comp : components)
  {
    comp->onDebugDraw();
  }

  for (BaseCollisionShape* shape : collisionShapes)
  {
    shape->onDebugDraw();
  }
}

void Entity::onUpdate()
{
  for (uint i = 0; i < components.size(); i++)
  {
    components[i]->onUpdate();
  }
}

void Entity::onLateUpdate()
{
  for (uint i = 0; i < components.size(); i++)
  {
    components[i]->onLateUpdate();
  }
}


//static functions
//----------------------------
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

void Entity::updateInstances()
{
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onUpdate();
  }
}

void Entity::lateUpdateInstances()
{
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onLateUpdate();
  }
}

struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};


void Entity::drawInstances()
{
  std::sort(Entity::entitys.begin(), Entity::entitys.end(), EntityLayerCompare());

  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onDraw();
  }
}

void Entity::debugDrawInstances()
{
  for (Entity* ent : entitys)
  {
    ent->onDebugDraw();
  }
}

void Entity::destroyQueuedInstances()
{
  bool found;
  Entity* ent;

  while (!Entity::queuedDestroyEntityIDs.empty())
  {
    uint id = Entity::queuedDestroyEntityIDs.front();
    ent = nullptr;
    found = false;

    //find entity with matching id, then remove from vector
    for (uint i = 0; i < Entity::entitys.size() && !found; i++)
    {
      if (Entity::entitys[i]->getID() == id)
      {
        ent = Entity::entitys[i];
        Entity::entitys.erase(Entity::entitys.begin() + i);
        found = true;
      }
    }
    //call onDestroy() and delete the object
    if (found)
    {
      ent->onDestroy();
      delete ent;
    }

    Entity::queuedDestroyEntityIDs.pop();
  }
}

void Entity::clearQueues()
{
  while (!queuedDestroyEntityIDs.empty())
  {
    queuedDestroyEntityIDs.pop();
  }

  while (!pendingEntityInstances.empty())
  {
    Entity* ent = pendingEntityInstances.front();
    pendingEntityInstances.pop();
    delete ent;
  }
}

void Entity::deleteAllEnts(bool isGlobalExempt)
{
  if (isGlobalExempt == true)
  {
    for (uint i = 0; i < Entity::entitys.size(); i++)
    {
      Entity* ent = Entity::entitys[i];
      if (ent->isGlobal == false)
      {
        Entity::entitys.erase(Entity::entitys.begin() + i);
        i--;
        delete ent;
      }
    }
  }
  else
  {
    for (uint i = 0; i < Entity::entitys.size(); i++)
    {
      Entity* ent = Entity::entitys[i];
      Entity::entitys.erase(Entity::entitys.begin() + i); 
      i--;
      delete ent;
    }
  }
}

void Entity::instantiateQueuedEnts()
{
  std::queue<Entity*> temp;
  //add all entity instances to the game
  while (!Entity::pendingEntityInstances.empty())
  {
    Entity* ent = Entity::pendingEntityInstances.front();
    Entity::entitys.push_back(ent);
    temp.push(ent);
    Entity::pendingEntityInstances.pop();
  }

  //call onStart() for all the newly added instances
  while (!temp.empty())
  {
    temp.front()->onStart();
    temp.pop();
  }
}


void Entity::onCollisionHit(Entity& hit)
{
  for (Component* comp : components)
  {
    comp->onCollisionHit(hit);
  }
}