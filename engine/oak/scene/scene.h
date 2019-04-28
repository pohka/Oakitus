#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "precache.h"

namespace oak
{
  //Handling of loading and unload Entitys and resources when changing scenes
  class Scene
  {
    public:
      friend class MetaData;

      Scene();
      ~Scene();

      //Loads the this scene
      virtual void onLoad() = 0;

      //Unloads this scene
      virtual void onUnload();

      const Precache& getPrecache();

    protected:
      Precache precache;
  };
}
#endif
