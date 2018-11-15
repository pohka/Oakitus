#ifndef SAMPLE_SCENE_H
#define SAMPLE_SCENE_H

#include "oak/core/scene.h"

namespace game
{
  class SampleScene : public oak::Scene
  {
    public:
      SampleScene();
      ~SampleScene();
      void onLoad() override;
      void onUnload() override;
  };
}

#endif