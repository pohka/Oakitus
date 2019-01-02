#include "scene.h"
#include "oakitus.h"
#include "entity.h"
#include "entity_manager.h"
#include "resources.h"
#include "../oak_def.h"

using namespace oak;

Scene* Scene::curScene = nullptr;
Scene* Scene::nextScene = nullptr;

Scene::Scene()
{
}

Scene::~Scene() {}

void Scene::onUnload()
{
  EntityManager::deleteAllEnts(true);
}

//static functions
//-----------------------

Scene* Scene::getCurrentScene()
{
  return curScene;
}

bool Scene::isNextSceneSet()
{
  return (nextScene != nullptr);
}

void Scene::loadFirstScene(Scene* scene)
{
  const Precache& precache = scene->getPrecache();

  for (std::string tex : precache.textures)
  {
    Resources::addTexture(tex);
  }
  for (std::string shader : precache.shaders)
  {
    Resources::addShader(shader);
  }
  for (std::string font : precache.fonts)
  {
    Resources::addFont(font);
  }

  curScene = scene;
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
void Scene::setNextScene(Scene& scene)
{
  nextScene = &scene;
}

const Precache& Scene::getPrecache()
{
  return precache;
}