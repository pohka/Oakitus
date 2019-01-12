#ifndef GROUND_CHECK_H
#define GROUND_CHECK_H

#include <oak/ecs/component.h>

namespace plat
{
  struct GroundCheck : public oak::Component
  {
    GroundCheck();
    void onTick() override;
  };
}


#endif