#ifndef DEMO_SCENE2_H
#define DEMO_SCENE2_H

#include <oak/core/scene.h>

namespace sample
{
  struct DemoScene2 : public oak::Scene
  {
    DemoScene2();
    void onLoad() override;
  };
}

#endif