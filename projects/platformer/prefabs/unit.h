#ifndef PLAT_UNIT_H
#define PLAT_UNIT_H

//#include <oak/ecs/actor.h>
#include "../plat_consts.h"

namespace plat
{
  struct Unit //: public oak::Actor
  {
    

    Unit() //: oak::Actor()
    {

    }

    virtual void onGroundTouch()
    {
      state = MOVE_STATE_ON_GROUND;
      jumpCount = maxJumpCount;
    }
    

    //variables
    uchar state = MOVE_STATE_FALLING;
    bool isPlayer = false;
    int jumpCount = 0;
    int maxJumpCount = 1;
    float height = 40.0f;
    float width = 34.0f;
    float speed = 100.0f;
    float airSpeedMultiplier = 0.7f;
    const float gravity = 100.0f;
    float maxJumpHeight = 150.0f;
    float jumpDuration = 1.0f;
    float jumpStartTime = -10.0f;

  };
}

#endif