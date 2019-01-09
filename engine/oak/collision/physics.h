#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <oak/core/types.h>
#include <limits>
#include "collision_layer.h"

namespace oak
{
  class Entity;

  struct RaycastHit2D
  {
    glm::vec2 point;
    glm::vec2 normal;
    float distance;
    Entity* entityHit;
  };

  struct Physics
  {

    static bool Raycast2D(const glm::vec3& origin, glm::vec3 direction, RaycastHit2D& hit, float distance, uint layers = COLLISION_LAYER_ALL);
  };
}

#endif