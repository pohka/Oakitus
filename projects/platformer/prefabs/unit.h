#ifndef PLAT_UNIT_H
#define PLAT_UNIT_H

#include <oak/ecs/actor.h>

namespace plat
{
  struct Unit : public oak::Actor
  {
    Unit() : oak::Actor()
    {

    }

    virtual void onGroundTouch()
    {
      isOnGround = true;
      jumpCount = maxJumpCount;
    }

    //variables
    bool isPlayer = false;
    bool isOnGround = false;
    int jumpCount = 0;
    int maxJumpCount = 1;
    float height = 40.0f;
    float width = 34.0f;
  };
}

#endif