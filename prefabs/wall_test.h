#ifndef WALL_TEST_H
#define WALL_TEST_H

#include "../oak/core/entity.h"

namespace game
{
  class WallTest : public oak::Entity
  {
    public:
      WallTest(float w, float h);
  };
}

#endif