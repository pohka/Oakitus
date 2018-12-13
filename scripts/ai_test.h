#ifndef AI_TEST_H
#define AI_TEST_H

#include <core/component.h>

namespace game
{
  class AITest : public oak::Component
  {
  public:
    AITest();

    void onUpdate() override;
  };
}

#endif