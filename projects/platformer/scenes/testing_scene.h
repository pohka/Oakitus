#ifndef TESTING_SCENE_H
#define TESTING_SCENE_H

#include <oak/scene/scene.h>

namespace plat
{
  struct TestingScene : public oak::Scene
  {
    TestingScene();
    ~TestingScene();

    void onLoad();
  };
}

#endif