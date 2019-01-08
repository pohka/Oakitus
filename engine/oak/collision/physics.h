#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <oak/core/types.h>
#include <limits>
#include "collision_layer.h"

namespace oak
{
  class Entity;

  struct RaycastHit
  {
    glm::vec3 point;
    glm::vec3 normal;
    float distance;
    Entity* entityHit;
  };

  struct Physics
  {

    static RaycastHit Raycast2D(const glm::vec3& origin, glm::vec3 direction, float distance, uint layers);
  };
}

#endif