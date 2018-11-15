#include "Oakitus.h"

using namespace oak;

GLWindow* Oakitus::glWindow = nullptr;
std::vector<Shader*> Oakitus::shaders;
std::vector<Entity*> Oakitus::entities;
IDGenerator* Oakitus::shaderIDGen = new IDGenerator();
Scene* Oakitus::curScene = nullptr;
uint Oakitus::defaultShaderID;
std::queue<uint> Oakitus::destroyEntIDQueue;
Camera* Oakitus::camera = nullptr;


void Oakitus::addEntity(Entity& entity)
{
  entities.push_back(&entity);
}

void Oakitus::addShader(Shader& shader)
{
  shaders.push_back(&shader);
}

void Oakitus::deleteAllEnts()
{
  for (uint i = 0; i < entities.size(); i++)
  {
    Entity* tmp = entities[i];
    entities.erase(entities.begin() + i); //remove from vector
    i--;
    delete tmp;
  }
}

void Oakitus::deleteAllEnts(std::vector<int> exceptionIDs)
{
  bool isException = false;
  for (uint i = 0; i < entities.size(); i++)
  {
    isException = false;
    uint entID = entities[i]->getID();
    for (uint a = 0; a < exceptionIDs.size() && !isException; a++)
    {
      if (entID == exceptionIDs[a])
      {
        isException = true;
      }
    }
    if (!isException)
    {
      Entity* tmp = entities[i];
      entities.erase(entities.begin() + i); //remove from vector
      i--;
      delete tmp;
    }
  }
}

void Oakitus::destroy(uint entityID)
{
  for (uint i = 0; i < entities.size(); i++)
  {
    if (entities[i]->getID() == entityID)
    {
      Entity* ent = entities[i];
      entities.erase(entities.begin() + i);
      delete ent;
    }
  }
}

void Oakitus::destroyEntityByID(uint entityID)
{
  destroyEntIDQueue.push(entityID);
}



Entity* Oakitus::findEntityByID(uint id)
{
  for (uint i = 0; i < entities.size(); i++)
  {
    if (entities[i]->getID() == id)
    {
      return entities[i];
    }
  }

  return nullptr;
}

Shader* Oakitus::findShaderByID(uint id)
{
  return shaders[0];
}


Shader* Oakitus::findShaderByName(std::string name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName().compare(name) == 0)
    {
      return shaders[i];
    }
  }
  return nullptr;
}


void Oakitus::onDestroy()
{
  while (!destroyEntIDQueue.empty())
  {
    uint id = destroyEntIDQueue.front();
    Entity* ent = nullptr;
    bool found = false;

    //find entity with matching id, then remove from vector
    for (uint i = 0; i < entities.size() && !found; i++)
    {
      if (entities[i]->getID() == id)
      {
        ent = entities[i];
        entities.erase(entities.begin() + i);
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


void Oakitus::onDraw()
{
  for (uint i = 0; i < entities.size(); i++)
  {
    entities[i]->onDraw();
  }
}

void Oakitus::onUpdate()
{
  for (uint i = 0; i < entities.size(); i++)
  {
    entities[i]->onUpdate();
  }
}

void Oakitus::setScene(Scene& scene)
{
  //unload and delete current scene
  if (curScene != nullptr) {
    curScene->onUnload();
    Scene* tmp = curScene;
    delete tmp;
  }
  //set and load new scene
  curScene = &scene;
  curScene->onLoad();
}
