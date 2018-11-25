#include "scene.h"
#include "store.h"
#include "oakitus.h"

using namespace oak;

Scene::Scene()
{
  
}

Scene::~Scene() {}

void Scene::onLoad()
{

}

void Scene::onUnload()
{
  Oakitus::deleteAllNonGlobalEntitys();
}