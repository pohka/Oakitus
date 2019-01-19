#ifndef PLAT_MOVEMENT_H
#define PLAT_MOVEMENT_H

#include <oak/ecs/component.h>
#include "../reflect.h"

namespace plat
{
  struct Movement : public oak::Component
  {
    Movement() : oak::Component(REFLECT_MOVEMENT, TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE) {}

    void applyMovement(float axisX, float axisY);
  };
}


#endif