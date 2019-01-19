#include "entity.h"
#include "component.h"
#include <oak/collision/base_collision_shape.h>
#include "entity_manager.h"
#include <oak/time/time.h>

using namespace oak;

Entity::Entity(bool isEverRendered, const uchar ENTITY_GROUP) : ENTITY_GROUP(ENTITY_GROUP)
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
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
  {
    for (Component* comp : componentGroups[i])
    {
      delete comp;
    }
  }

  detach();
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
  EntityManager::queueEntityCreate(this);
}

void oak::Entity::create(float x, float y)
{
  transform->moveTo(x, y, 0.0f);
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
  for (uchar i = 0; i < TICK_GROUP_MAX; i++)
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
  //parent already set to this
  if (child->parent == this)
  {
    return;
  }

  //queue to be created if not created yet
  if (child->creationState == CREATION_STATE_NULL)
  {
    child->parent = this;
    EntityManager::queueEntityCreate(child);
  }
  //attach a entity that is already created
  else if(child->creationState == CREATION_STATE_CREATED)
  {
    child->transform->onParentSet(transform);
    child->parent = this;
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

BaseRigidBody* Entity::getRigidBody() const
{
  return rigidBody;
}

void Entity::setCreationState(const uchar state)
{
  creationState = state;
}

const uchar Entity::getCreationState() const
{
  return creationState;
}