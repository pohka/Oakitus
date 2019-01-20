#ifndef CHESS_SCENE_1_H
#define CHESS_SCENE_1_H

#include <oak/oak.h>

namespace chess
{
  class Scene1 : public oak::Scene
  {

    public:
      Scene1();
      void onLoad() override;
  };
}

#endif