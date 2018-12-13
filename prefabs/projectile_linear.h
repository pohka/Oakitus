#ifndef PROJECTILE_LINEAR_H
#define PROJECTILE_LINEAR_H

#include "projectile.h"

namespace game
{
  namespace prefab
  {
    class ProjectileLinear : public Projectile
    {
      public:
        ProjectileLinear(
          glm::vec2 targetPos,
          Unit& caster,
          uint abilityID,
          DamageData damage,
          float speed,
          float radius,
          float maxDistance = 1000.0f,
          bool destroyOnHit = true,
          uchar targetTeam = TARGET_TEAM_ENEMY
        );
        void onStart();
        void onUpdate();

      protected:
        float maxDistance;
        glm::vec2 velocity;
    };
  }
}

#endif
