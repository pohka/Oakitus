#ifndef LINEAR_PROJECTILE_H
#define LINEAR_PROJECTILE_H

#include <core/script.h>
#include <glm/glm.hpp>

namespace game
{
  class LinearProjectile : public oak::Script
  {
    glm::vec2 targetPos;
    glm::vec2 spawnOrigin;
    glm::vec2 velocity;
    float maxDistance;
    bool destroyOnHit;
    float speed;
    

    public:
      LinearProjectile(
        glm::vec2 targetPos,
        float speed,
        float maxDistance,
        bool destroyOnHit
      );
      ~LinearProjectile();

      void onStart() override;
      void onUpdate() override;
  };
}

#endif