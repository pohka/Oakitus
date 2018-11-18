#include "scene.h"
#include "store.h"

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
  Store::deleteAllNonGlobalEntitys();
}