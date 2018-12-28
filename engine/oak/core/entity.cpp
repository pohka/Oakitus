#include "entity.h"
#include "component.h"
#include <oak/collision/base_collision_shape.h>
#include <oak/debug.h>
#include "entity_manager.h"

using namespace oak;




Entity::Entity() 
{
  //set default values
  componentIDGen = IDGenerator();
  this->entityID = EntityManager::nextEntityID();
  this->position = glm::vec3(0, 0, 0);
  this->rotation = glm::vec3(0, 0, 0);
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
  collisionLayer = CollisionLayer::NONE;
}

Entity::~Entity()
{
  for (Component* c : components)
  {
    delete c;
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

void Entity::create()
{
  EntityManager::pendingEntityInstances.push(this);
}

void oak::Entity::create(float x, float y)
{
  this->position.x = x;
  this->position.y = y;
  EntityManager::pendingEntityInstances.push(this);
}

void Entity::destroy()
{
  EntityManager::queuedDestroyEntityIDs.push(entityID);
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

void Entity::onCreate()
{
  for (Component* comp : components)
  {
    comp->onCreate();
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

void Entity::onTick(const uchar TICK_GROUP)
{
  for (Component* comp : components)
  {
    if (comp->getTickGroup() == TICK_GROUP)
    {
      comp->onTick();
    }
  }
}





void Entity::onCollisionHit(Entity& hit)
{
  for (Component* comp : components)
  {
    comp->onCollisionHit(hit);
  }
}

bool Entity::getIsTickingEnabled() const
{
  return isTickingEnable;
}

void Entity::setIsTickingEnabled(bool isEnabled)
{
  isTickingEnable = isEnabled;
}