#include "scene.h"
#include "oakitus.h"
#include "entity.h"
#include "entity_manager.h"
#include <oak/event/event_manager.h>
#include "player_resource.h"


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

