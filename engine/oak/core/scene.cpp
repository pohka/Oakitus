#include "scene.h"
#include "oakitus.h"
#include "entity.h"
#include "entity_manager.h"


using namespace oak;

Scene::Scene()
{
}

Scene::~Scene() {}

void Scene::onUnload()
{
  EntityManager::deleteAllEnts(true);
}

const Precache& Scene::getPrecache()
{
  return precache;
}

