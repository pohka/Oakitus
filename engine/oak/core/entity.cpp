#include "entity.h"
#include "component.h"
#include <oak/collision/base_collision_shape.h>
#include <oak/debug.h>
#include "entity_manager.h"

using namespace oak;

Entity::Entity(bool isEverRendered)
{
  this->isEverRendered = isEverRendered;
  this->isRenderable = isEverRendered;

  this->entityID = EntityManager::entityIDGen.nextID();
  this->position = glm::vec3(0, 0, 0);
  this->rotation = glm::vec3(0, 0, 0);
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
  collisionLayer = CollisionLayer::NONE;
}

Entity::~Entity()
{
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      delete comp;
    }
  }
}

void Entity::addComponent(Component* component)
{
  //give the component a unique ID and tell it who its owner entity is
  component->entity = this;
  component->componentID = componentIDGen.nextID();

  //add to tick group
  uchar tickGroup = component->getTickGroup();
  componentGroups[tickGroup].push_back(component);
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
  uchar tickGroup = rigidBody->getTickGroup();
  componentGroups[tickGroup].push_back(rigidBody);
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
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onCreate();
    }
  }
}

void Entity::onDestroy()
{
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onDestroy();
    }
  }
}

void Entity::onRender() const
{
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      if (comp->getIsRenderable())
      {
        comp->onRender();
      }
    }
  }
}

void Entity::onDebugDraw() const
{
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onDebugDraw();
    }
  }

  for (BaseCollisionShape* shape : collisionShapes)
  {
    shape->onDebugDraw();
  }
}

void Entity::onTick(const uchar TICK_GROUP)
{
  for (Component* comp : componentGroups[TICK_GROUP])
  {
    if (comp->canTickThisFrame())
    {
      comp->onTick();
    }
  }
}

void Entity::onCollisionHit(Entity& hit)
{
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onCollisionHit(hit);
    }
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

void Entity::setIsVisible(bool isVisible)
{
  if (isEverRendered)
  {
    isRenderable = isVisible;
  }
}

bool Entity::getIsRenderable() const
{
  return isRenderable;
}

bool Entity::getCanTickWhenPaused() const
{
  return canTickWhenPaused;
}

bool Entity::canTickThisFrame() const
{
  bool isPaused = Time::getIsPaused();
  if (isTickingEnable && 
    ((isPaused && canTickWhenPaused) || !isPaused))
  {
    return true;
  }

  return false;
}