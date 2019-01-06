#include "entity.h"
#include "component.h"
#include <oak/collision/base_collision_shape.h>
#include "entity_manager.h"
#include <oak/time/time.h>

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
  //destruct child entities
  for (Entity* child : children)
  {
    delete child;
  }

  //destruct components
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      delete comp;
    }
  }

  //notify parent of destruction
  if (parent != nullptr)
  {
    parent->onChildDestroyed(entityID);
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
  if (createState == STATE_NOT_CREATED)
  {
    EntityManager::pendingEntityInstances.push(this);
    createState = STATE_QUEUED;
  }
}

void oak::Entity::create(float x, float y)
{
  if (createState == STATE_NOT_CREATED)
  {
    this->position.x = x;
    this->position.y = y;
    EntityManager::pendingEntityInstances.push(this);
    createState = STATE_QUEUED;
  }
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
  createState = STATE_CREATED;

  //onCreate components
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onCreate();
    }
  }

  //onCreate children
  for (Entity* child : children)
  {
    child->onCreate();
  }

  //notify parent
  if (parent != nullptr)
  {
    parent->onChildCreated(this);
  }
}

void Entity::onDestroy()
{
  //onDestroy children
  for (Entity* child : children)
  {
    child->onDestroy();
  }

  //onDestroy components
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
  //render components
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

  //render children
  for (Entity* child : children)
  {
    child->onRender();
  }
}

void Entity::onDebugDraw() const
{
  //components
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onDebugDraw();
    }
  }

  //collision
  for (BaseCollisionShape* shape : collisionShapes)
  {
    shape->onDebugDraw();
  }

  //children
  for (Entity* child : children)
  {
    child->onDebugDraw();
  }
}

void Entity::onTick(const uchar TICK_GROUP)
{
  //components
  for (Component* comp : componentGroups[TICK_GROUP])
  {
    if (comp->canTickThisFrame())
    {
      comp->onTick();
    }
  }

  //children
  for (Entity* child : children)
  {
    child->onTick(TICK_GROUP);
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
  //if parent can't tick then override self
  if (parent != nullptr && parent->getIsTickingEnabled() == false)
  {
    return false;
  }
  return isTickingEnable;
}

void Entity::setIsTickingEnabled(bool isEnabled)
{
  isTickingEnable = isEnabled;
}

void Entity::setIsRenderable(bool isRenderable)
{
  if (isEverRendered)
  {
    this->isRenderable = isRenderable;
  }
}

bool Entity::getIsRenderable() const
{
  //if parent is not renderable then override self
  if (parent != nullptr && parent->getIsRenderable() == false)
  {
    return false;
  }
  return isRenderable;
}

bool Entity::getCanTickWhenPaused() const
{
  //if parent is not  tickable when pased then override self
  if (parent != nullptr && parent->canTickThisFrame() == false)
  {
    return false;
  }
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

std::vector<BaseCollisionShape*>& Entity::getCollisionShapes()
{
  return collisionShapes;
}

void Entity::addChild(Entity* child)
{
  child->parent = this;

  if (child->createState == STATE_NOT_CREATED)
  {
    EntityManager::pendingEntityInstances.push(child);
    child->createState = STATE_QUEUED;
  }
  else if(child->createState == STATE_CREATED)
  {
    children.push_back(child);
  }
}

Entity* Entity::findChildByName(std::string name)
{
  for (Entity* ent : children)
  {
    if (ent->name == name)
    {
      return ent;
    }
  }

  return nullptr;
}

Entity* Entity::findChildByID(uint id)
{
  for (Entity* ent : children)
  {
    if (ent->entityID == id)
    {
      return ent;
    }
  }

  return nullptr;
}

void Entity::onChildDestroyed(uint entID)
{
  for (uint i = 0; i < children.size(); i++)
  {
    if (children[i]->entityID == entID)
    {
      children.erase(children.begin() + i);
      return;
    }
  }
}

void Entity::onChildCreated(Entity* child)
{
  children.push_back(child);
}