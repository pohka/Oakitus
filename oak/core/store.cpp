#include "store.h"

using namespace oak;


Scene* Store::curScene = nullptr;
Scene* Store::nextScene = nullptr;

Scene* Store::getCurrentScene()
{
  return curScene;
}

bool Store::isNewSceneSet()
{
  return (nextScene != nullptr);
}

void Store::loadFirstScene(Scene& scene)
{
  curScene = &scene;
  curScene->onLoad();
}


struct EntityLayerCompare {
  bool operator()(const Entity* l, const Entity* r) {
    return l->layerID < r->layerID;
  }
};


void Store::onSceneChange()
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

void Store::reloadScene()
{
  curScene->onUnload();
  curScene->onLoad();
}
//
void Store::setScene(Scene& scene)
{
  nextScene = &scene;
}
