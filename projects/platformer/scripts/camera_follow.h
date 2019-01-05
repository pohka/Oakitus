#ifndef CAMERA_FOLLOW_H
#define CAMERA_FOLLOW_H

#include <oak/oak.h>

namespace plat
{
  struct CameraFollow : oak::Component
  {
    CameraFollow();

    void setTarget(oak::Entity* target);
    
    void onTick() override;

  private:
    uint targetID = 0;
  };
}

#endif