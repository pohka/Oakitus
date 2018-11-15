#include "Scene.h"

#include "Oakitus.h"

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
  //todo: dealocate the rest of the scene
  Oakitus::deleteAllEnts();
}