#include "scene.h"
#include <oak/core/oakitus.h>
#include <oak/ecs/entity.h>
#include <oak/ecs/entity_manager.h>
#include <oak/event/event_manager.h>
#include <oak/player/player_resource.h>


using namespace oak;

Scene::Scene()
{
}

Scene::~Scene() {}

void Scene::onUnload()
{
  EntityManager::deleteAllEnts(true);
  EventManager::removeAllEvents();
}

const Precache& Scene::getPrecache()
{
  return precache;
}

