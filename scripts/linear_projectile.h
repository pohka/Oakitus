#ifndef LINEAR_PROJECTILE_H
#define LINEAR_PROJECTILE_H

#include <core/component.h>
#include <glm/glm.hpp>
#include <core/entity.h>
#include "../ability.h"

namespace game
{
  //class Entity;

  class LinearProjectile : public oak::Component
  {
    glm::vec2 targetPos;
    glm::vec2 spawnOrigin;
    glm::vec2 velocity;
    float maxDistance;
    bool destroyOnHit;
    float speed;
    uchar targetTeam;
    Faction casterFaction;

    

    public:
      LinearProjectile(
        glm::vec2 targetPos,
        float speed,
        float maxDistance,
        bool destroyOnHit,
        uchar targetTeam,
        Faction casterFaction
      );
      ~LinearProjectile();

      void onStart() override;
      void onUpdate() override;
      void onCollisionHit(oak::Entity& hit) override;
  };
}

#endif