#include "store.h"

using namespace oak;

GLWindow* Store::glWindow = nullptr;
std::vector<Entity*> Store::entitys;
Scene* Store::curScene = nullptr;
Scene* Store::nextScene = nullptr;
std::queue<uint> Store::destroyEntIDQueue;
Camera* Store::camera = nullptr;


void Store::addEntity(Entity& entity)
{
  entitys.push_back(&entity);
}

void Store::deleteAllEntitys()
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    Entity* tmp = entitys[i];
    entitys.erase(entitys.begin() + i); //remove from vector
    i--;
    delete tmp;
  }
}

void Store::destroy(uint entityID)
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    if (entitys[i]->getID() == entityID)
    {
      Entity* ent = entitys[i];
      entitys.erase(entitys.begin() + i);
      delete ent;
    }
  }
}

void Store::destroyEntityByID(uint entityID)
{
  destroyEntIDQueue.push(entityID);
}



Entity* Store::findEntityByID(uint id)
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

Entity* Store::findEntityByName(std::string name)
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

std::vector<Entity*> Store::getGlobalEntitys()
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

bool Store::isNewSceneSet()
{
  return (nextScene != nullptr);
}

void Store::onDestroy()
{
  while (!destroyEntIDQueue.empty())
  {
    uint id = destroyEntIDQueue.front();
    Entity* ent = nullptr;
    bool found = false;

    //find entity with matching id, then remove from vector
    for (uint i = 0; i < entitys.size() && !found; i++)
    {
      if (entitys[i]->getID() == id)
      {
        ent = entitys[i];
        entitys.erase(entitys.begin() + i);
        found = true;
      }
    }
    //call onDestroy and delete the object
    if (found)
    {
      ent->onDestroy();
      delete ent;
    }

    destroyEntIDQueue.pop();
  }
}

struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};

void Store::onDraw()
{
  std::sort(entitys.begin(), entitys.end(), EntityLayerCompare());

  for (uint i = 0; i < entitys.size(); i++)
  {
    entitys[i]->onDraw();
  }
}

void Store::onUpdate()
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    entitys[i]->onUpdate();
  }
}

void Store::loadFirstScene(Scene& scene)
{
  curScene = &scene;
  curScene->onLoad();
}

void Store::setScene(Scene& scene)
{
  nextScene = &scene;
}

void Store::onSceneChange()
{
  //unload and delete current scene
  curScene->onUnload();
  Scene* tmp = curScene;
  delete tmp;

  //set and load next scene
  curScene = nextScene;
  nextScene = nullptr;
  curScene->onLoad();
}

void Store::deleteAllNonGlobalEntitys()
{
  for (uint i = 0; i < entitys.size(); i++)
  {
    Entity* ent = entitys[i];
    if (ent->isGlobal == false)
    {
      entitys.erase(entitys.begin() + i); //remove from vector
      i--;
      delete ent;
    }
  }
}