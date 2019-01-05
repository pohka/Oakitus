#ifndef CAMERA_ENT_H
#define CAMERA_ENT_H

#include <oak/oak.h>
#include "../scripts/camera_follow.h"

namespace plat
{
  struct CameraEnt : oak::Entity
  {
    CameraEnt() : Entity(true)
    {
      addComponent(new CameraFollow());
    }
  };
}

#endif