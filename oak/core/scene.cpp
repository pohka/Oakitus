#include "scene.h"
#include "oakitus.h"
#include "entity.h"

using namespace oak;

Scene* Scene::curScene = nullptr;
Scene* Scene::nextScene = nullptr;

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

//static functions
//-----------------------

Scene* Scene::getCurrentScene()
{
  return curScene;
}

bool Scene::isNewSceneSet()
{
  return (nextScene != nullptr);
}

void Scene::loadFirstScene(Scene& scene)
{
  curScene = &scene;
  curScene->onLoad();
}


struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};


void Scene::swapScene()
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

void Scene::reloadScene()
{
  curScene->onUnload();
  curScene->onLoad();
}
//
void Scene::setScene(Scene& scene)
{
  nextScene = &scene;
}