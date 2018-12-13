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
      int damage;
      uint abilityID;
      uint casterID;

    public:
      Projectile(glm::vec2 targetPos, Unit& caster, uint abilityID);
      ~Projectile();

      void onStart() override;
      void onUpdate() override;
      void onCollisionHit(oak::Entity& hit) override;
      void onProjectileHit(Unit& unitHit);
    };
  }
}

#endif