#ifndef SAMPLE_SCENE_H
#define SAMPLE_SCENE_H

#include "core/scene.h"

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