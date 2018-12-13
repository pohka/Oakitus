#include "projectile.h"
#include <oak.h>
#include "../ability.h"
#include <debug.h>
#include "../global_funcs.h"


using namespace game::prefab;
using namespace oak;
using namespace game;

Projectile::Projectile(
  glm::vec2 targetPos,
  Unit& caster,
  uint abilityID,
  DamageData damage,
  float speed,
  float radius,
  bool destroyOnHit,
  uchar targetTeam
)
{
  this->targetPos = targetPos;
  this->abilityID = abilityID;
  this->damage = damage;
  this->speed = speed;
  this->destroyOnHit = destroyOnHit;
  this->targetTeam = targetTeam;
  casterFaction = caster.getFaction();
  casterID = caster.getID();

  addCollision(new CollisionCircle(radius, 0.0f, 0.0f));
  this->collisionLayer = CollisionLayer::PROJECTILE;
}

Projectile::~Projectile()
{
  
}

void Projectile::onCollisionHit(Entity& hit)
{
  if (hit.getCollisionLayer() == CollisionLayer::UNIT)
  {
    Unit& unitHit = static_cast<Unit&>(hit);

    if (
      (targetTeam == TARGET_TEAM_ENEMY && unitHit.getFaction() != casterFaction) ||
      (targetTeam == TARGET_TEAM_FRIENDLY && unitHit.getFaction() == casterFaction) ||
      (targetTeam == TARGET_TEAM_BOTH)
      )
    {
      onProjectileHit(unitHit);

      if (destroyOnHit)
      {
        destroy();
      }
    }
  }
}

void Projectile::onProjectileHit(Unit& unitHit)
{
  damage.victimID = unitHit.getID();
  applyDamage(damage);
}