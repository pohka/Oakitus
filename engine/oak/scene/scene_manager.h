#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"

namespace oak
{
  struct SceneManager
  {
    friend class Oakitus;

    //Returns the current scene
    static Scene* getCurrentScene();

    //Reloads the current scene
    static void  reloadScene();

    //Returns true if the next scene has been set<
    static bool isNextSceneSet();

    //Should be called once to load the first scene in Oakitus::load()
    static void loadFirstScene(Scene* scene);

    //Sets and swaps out the next scene
    static void setNextScene(Scene* scene);

    private:
      //waps out the next scene
      static void swapScene();

      static Scene* curScene; //Current scene
      static Scene* nextScene; //Pointer for when the next scene is queued

  };
}

#endif