#include "entity.h"
#include "component.h"
#include <oak/collision/collision_shape.h>
#include "entity_manager.h"
#include <oak/time/time.h>

using namespace oak;

Entity::Entity(bool isEverRendered, uchar ENTITY_GROUP) : ENTITY_GROUP(ENTITY_GROUP)
{
  this->isEverRendered = isEverRendered;
  this->isRenderable = isEverRendered;

  this->entityID = EntityManager::nextEntityID();
  layerID = 0;
  isGlobal = false;
  this->name = "ent_" + std::to_string(entityID);
  transform = new Transform();
  addComponent(transform);
}

Entity::~Entity()
{
  //destruct child entities
  for (Entity* child : children)
  {
    delete child;
  }

  //destruct components
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      delete comp;
    }
  }

  detach();
}



void Entity::addComponent(Component* component, bool isRigidBody)
{
  //give the component a unique ID and tell it who its owner entity is
  component->entity = this;
  component->componentID = componentIDGen.nextID();

  //add to tick group
  uchar tickGroup = static_cast<uchar>(component->getTickGroup());
  componentGroups[tickGroup].push_back(component);

  if (isRigidBody)
  {
    rigidbody = static_cast<BaseRigidBody*>(component);
  }
}

BaseRigidBody* Entity::getRigidBody() const
{
  return rigidbody;
}

void Entity::addCollision(CollisionShape* shape)
{
  shape->entity = this;
  collisionShapes.push_back(shape);
}

void Entity::create()
{
  EntityManager::queueEntityCreate(this);
}

void oak::Entity::create(float x, float y, float z)
{
  transform->moveTo(x, y, z);
  EntityManager::queueEntityCreate(this);
}

void Entity::destroy()
{
  EntityManager::queueEntityDestroy(this);
}


uint Entity::getID() const
{
  return this->entityID;
}

const uint Entity::getCollisionLayer() const
{
  return collisionLayer;
}

std::string Entity::getName() const
{
  return name;
}

void Entity::onCreate()
{
  //children will call onCreate for themselves

  //onCreate components
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onCreate();
    }
  }

  //notify parent
  if (parent != nullptr)
  {
    parent->children.push_back(this);
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
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
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
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
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
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      comp->onDebugDraw();
    }
  }

  //collision
  for (CollisionShape* shape : collisionShapes)
  {
    shape->onDebugDraw();
  }

  //children
  for (Entity* child : children)
  {
    child->onDebugDraw();
  }
}

void Entity::onTick(Component::TickGroup tickGroup)
{
  //components
  for (Component* comp : componentGroups[static_cast<unsigned int>(tickGroup)])
  {
    if (comp->canTickThisFrame())
    {
      comp->onTick();
    }
  }

  //children
  for (Entity* child : children)
  {
    child->onTick(tickGroup);
  }
}

void Entity::onCollisionHit(Entity& hit)
{
  for (uchar i = 0; i < Component::TICK_GROUP_COUNT; i++)
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

std::vector<CollisionShape*>& Entity::getCollisionShapes()
{
  return collisionShapes;
}

void Entity::addChild(Entity* child)
{
  //parent already set to this
  if (child->parent == this)
  {
    return;
  }

  //queue to be created if not created yet
  if (child->creationState == CreationState::NONE)
  {
    child->parent = this;
    EntityManager::queueEntityCreate(child);
  }
  //attach a entity that is already created
  else if(child->creationState == CreationState::CREATED)
  {
    child->transform->onParentSet(transform);
    child->parent = this;
    children.push_back(child);
  }
}

Entity* Entity::findChildByName(const std::string& name)
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

void Entity::detach()
{
  if (parent != nullptr)
  {
    //set transform to world coords
    transform->onParentSet(nullptr);

    //erase this entity from children vector in parent
    for (uint i = 0; i < parent->children.size(); i++)
    {
      if (parent->children[i]->entityID == entityID)
      {
        parent->children.erase(parent->children.begin() + i);
        break;
      }
    }
    parent = nullptr;
  }
}

const std::vector<Entity*>& Entity::getChildren() const
{
  return children;
}

const Entity* Entity::getParent() const
{
  return parent;
}

void Entity::setCreationState(CreationState state)
{
  creationState = state;
}

Entity::CreationState Entity::getCreationState() const
{
  return creationState;
}