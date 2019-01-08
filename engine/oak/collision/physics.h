#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <oak/core/types.h>
#include <limits>
#include "collision_layer.h"

namespace oak
{
  

  struct RaycastHit
  {

  };

  struct Physics
  {

    static RaycastHit Raycast2D(const glm::vec3& origin, const glm::vec3& direction, float dist, uint layers)
    {

    }
  };
}

#endif