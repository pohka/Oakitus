#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <oak/core/entity.h>
#include "../ability.h"
#include "../unit.h"

namespace game
{

  namespace prefab
  {
    class Projectile : public oak::Entity
    {
      public:
        Projectile(
          glm::vec2 targetPos,
          Unit& caster,
          uint abilityID,
          DamageData damage,
          float speed,
          float radius,
          bool destroyOnHit = true,
          uchar targetTeam = TARGET_TEAM_ENEMY
        );
        ~Projectile();

        virtual void onCreate() = 0;
        virtual void onUpdate() = 0;
        void onCollisionHit(oak::Entity& hit);
        virtual void onProjectileHit(Unit& unitHit);

      protected:
        glm::vec2 targetPos;
        glm::vec2 spawnOrigin;
        bool destroyOnHit;
        float speed;
        uchar targetTeam;
        uchar casterFaction;
        DamageData damage;
        uint abilityID;
        uint casterID;
    };
  }
}

#endif