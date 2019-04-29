#include "entity_manager.h"
#include <oak/time/time.h>

using namespace oak;

std::vector<Entity*> EntityManager::entitys;
std::queue<uint> EntityManager::queuedDestroyEntityIDs;
IDGenerator EntityManager::entityIDGen;
std::queue<Entity*> EntityManager::pendingEntityInstances;
std::vector<DestroyRequest> EntityManager::destroyRequests = {};


Entity* EntityManager::findEntityByID(uint id)
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

Entity* EntityManager::findEntityByName(std::string name)
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

std::vector<Entity*> EntityManager::getGlobalEntitys()
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

void EntityManager::tickInstances(Component::TickGroup tickGroup)
{
  for (Entity* ent : EntityManager::entitys)
  {
    if (ent->canTickThisFrame())
    {
      ent->onTick(tickGroup);
    }
  }
}

void EntityManager::destroyEntityByID(uint id)
{
  queuedDestroyEntityIDs.push(id);
}

struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};


void EntityManager::drawInstances()
{
  std::sort(entitys.begin(), EntityManager::entitys.end(), EntityLayerCompare());

  for (Entity* ent : EntityManager::entitys)
  {
    if (ent->getIsRenderable())
    {
      ent->onRender();
    }
  }
}

void EntityManager::debugDrawInstances()
{
  for (Entity* ent : entitys)
  {
    ent->onDebugDraw();
  }
}

void EntityManager::destroyQueuedInstances()
{
  bool found;
  Entity* ent;

  while (!queuedDestroyEntityIDs.empty())
  {
    uint id = queuedDestroyEntityIDs.front();
    ent = nullptr;
    found = false;

    //find entity with matching id, then remove from vector
    for (uint i = 0; i < EntityManager::entitys.size() && !found; i++)
    {
      if (EntityManager::entitys[i]->getID() == id)
      {
        ent = EntityManager::entitys[i];
        EntityManager::entitys.erase(EntityManager::entitys.begin() + i);
        found = true;
      }
    }
    //call onDestroy() and delete the object
    if (found)
    {
      ent->onDestroy();
      delete ent;
    }

    EntityManager::queuedDestroyEntityIDs.pop();
  }
}

void EntityManager::clearQueues()
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

void EntityManager::deleteAllEnts(bool isGlobalExempt)
{
  if (isGlobalExempt == true)
  {
    for (uint i = 0; i < EntityManager::entitys.size(); i++)
    {
      Entity* ent = EntityManager::entitys[i];
      if (ent->isGlobal == false)
      {
        EntityManager::entitys.erase(EntityManager::entitys.begin() + i);
        i--;
        delete ent;
      }
    }
  }
  else
  {
    for (uint i = 0; i < EntityManager::entitys.size(); i++)
    {
      Entity* ent = EntityManager::entitys[i];
      EntityManager::entitys.erase(EntityManager::entitys.begin() + i);
      i--;
      delete ent;
    }
  }
  destroyRequests.clear();
}

void EntityManager::instantiateQueuedEnts()
{
  std::queue<Entity*> temp;
  //add all entity instances to the game
  while (!EntityManager::pendingEntityInstances.empty())
  {
    Entity* ent = pendingEntityInstances.front();
    ent->setCreationState(Entity::CreationState::CREATED);
    entitys.push_back(ent);
    temp.push(ent);
    pendingEntityInstances.pop();
  }

  //call onStart() for all the newly added instances
  while (!temp.empty())
  {
    temp.front()->onCreate();
    temp.pop();
  }
}

std::vector<Entity*>& EntityManager::getAllEntitys()
{
  return entitys;
}

void EntityManager::queueEntityCreate(Entity* ent)
{
  if (ent->creationState == Entity::CreationState::NONE)
  {
    ent->setCreationState(Entity::CreationState::QUEUED);
    pendingEntityInstances.push(ent);
  }
}

void EntityManager::queueEntityDestroy(Entity* ent)
{
  if (ent->creationState < Entity::CreationState::DESTROYED)
  {
    ent->setCreationState(Entity::CreationState::DESTROYED);
    queuedDestroyEntityIDs.push(ent->getID());
  }
}

const uint EntityManager::nextEntityID()
{
  return entityIDGen.nextID();
}

void EntityManager::getAllEntitysByGroup(const uchar ENTITY_GROUP, std::vector<Entity*>& out)
{
  for (Entity* ent : entitys)
  {
    if (ent->ENTITY_GROUP == ENTITY_GROUP)
    {
      out.push_back(ent);
    }
  }
}

void EntityManager::requestDestroy(const uint entID, const float delay)
{
  destroyRequests.push_back({ entID, delay + Time::getGameTime() });
}

//moves requested destroys to queuedDestroys
void EntityManager::checkRequestedDestroys()
{
  const float now = Time::getGameTime();
  for (uint i = 0; i < destroyRequests.size(); i++)
  {
    if (now >= destroyRequests[i].destroyTime)
    {
      queuedDestroyEntityIDs.push(destroyRequests[i].entID);
      destroyRequests.erase(destroyRequests.begin() + i);
      i--;
    }
  }
}