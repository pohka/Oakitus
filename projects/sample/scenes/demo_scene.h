#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include <oak/oak.h>

namespace sample
{
  struct DemoScene : public oak::Scene
  {
    DemoScene();
    void onLoad() override;
  };
}

#endif