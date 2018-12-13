#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <core/entity.h>
#include "../ability.h"
#include "../unit.h"

namespace game
{

  namespace prefab
  {
    class Projectile : public oak::Entity
    {
      glm::vec2 targetPos;
      glm::vec2 spawnOrigin;
      glm::vec2 velocity;
      float maxDistance;
      bool destroyOnHit;
      float speed;
      uchar targetTeam;
      uchar casterFaction;
      DamageData damage;
      uint abilityID;
      uint casterID;

    public:
      Projectile(
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
      ~Projectile();

      void onStart();
      void onUpdate();
      void onCollisionHit(oak::Entity& hit);
      void onProjectileHit(Unit& unitHit);
    };
  }
}

#endif