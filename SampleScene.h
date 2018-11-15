#ifndef SAMPLE_SCENE_H
#define SAMPLE_SCENE_H

#include "Scene.h"

namespace oak
{
  class SampleScene : public Scene
  {
    public:
      SampleScene();
      ~SampleScene();
      void onLoad() override;
      void onUnload() override;
  };
}

#endif