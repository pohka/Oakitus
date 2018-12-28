#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include <oak/core/scene.h>

namespace sample
{
  struct DemoScene : public oak::Scene
  {
    void onLoad() override;
  };
}

#endif