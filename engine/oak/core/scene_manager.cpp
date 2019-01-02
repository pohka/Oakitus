#include "scene_manager.h"
#include "resources.h"

using namespace oak;

Scene* SceneManager::curScene = nullptr;
Scene* SceneManager::nextScene = nullptr;


Scene* SceneManager::getCurrentScene()
{
  return curScene;
}

bool SceneManager::isNextSceneSet()
{
  return (nextScene != nullptr);
}

void SceneManager::loadFirstScene(Scene* scene)
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


void SceneManager::swapScene()
{
  //unload and delete current scene
  curScene->onUnload();
  //Scene* tmp = curScene;
  delete curScene;

  //set and load next scene
  curScene = nextScene;
  nextScene = nullptr;
  curScene->onLoad();
}

void SceneManager::reloadScene()
{
  curScene->onUnload();
  curScene->onLoad();
}
//
void SceneManager::setNextScene(Scene* scene)
{
  nextScene = scene;
}

void SceneManager::diffCache()
{

}