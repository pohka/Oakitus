#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include <oak/core/scene.h>

namespace sample
{
  struct DemoScene : public oak::Scene
  {
    DemoScene();
    void onLoad() override;
    void onUnload() override;
  };
}

#endif