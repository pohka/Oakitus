#include "oakitus.h"
#include "time.h"
#include "input.h"
#include "camera.h"
#include "entity.h"
#include <glm/glm.hpp>
#include "debug.h"

using namespace oak;

void Oakitus::init()
{
  Time::init();
  Input::init();

  Camera::init(
    glm::vec3(0.0f, 0.0f, 5.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f, //field or view
    true
  );
}

void Oakitus::updateEnts()
{
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onUpdate();
  }
}

struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};

void Oakitus::drawEnts()
{
  std::sort(Entity::entitys.begin(), Entity::entitys.end(), EntityLayerCompare());

  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity::entitys[i]->onDraw();
  }
}

void Oakitus::destroyQueue()
{
  while (!Entity::destroyEntIDQueue.empty())
  {
    uint id = Entity::destroyEntIDQueue.front();
    Entity* ent = nullptr;
    bool found = false;
  
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
    //call onDestroy and delete the object
    if (found)
    {
      //LOG << "destroyed:" << ent->getName() << ":" << ent->getID();
      ent->onDestroy();
      delete ent;
    }
  
    Entity::destroyEntIDQueue.pop();
  }
}


void Oakitus::deleteAllNonGlobalEntitys()
{
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    Entity* ent = Entity::entitys[i];
    if (ent->isGlobal == false)
    {
      Entity::entitys.erase(Entity::entitys.begin() + i); //remove from vector
      i--;
      delete ent;
    }
  }
}