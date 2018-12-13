//#include "linear_projectile.h"
//#include <oak.h>
//#include "../unit.h"
////#include "../global_funcs.h"
//
//using namespace game;
//using namespace oak;
//
//LinearProjectile::LinearProjectile(
//  glm::vec2 targetPos,
//  int damage,
//  float speed,
//  float maxDistance,
//  bool destroyOnHit,
//  uchar targetTeam,
//  uchar casterFaction,
//  uint abilityID,
//  uint casterID
//)
//{
//  this->damage = damage;
//  this->targetPos = targetPos;
//  this->speed = speed;
//  this->maxDistance = maxDistance;
//  this->destroyOnHit = destroyOnHit;
//  this->targetTeam = targetTeam;
//  this->casterFaction = casterFaction;
//  this->casterID = casterID;
//  this->abilityID = abilityID;
//}
//
//LinearProjectile::~LinearProjectile()
//{
//
//}
//
//void LinearProjectile::onStart()
//{
//  this->spawnOrigin = glm::vec2(entity->position.x, entity->position.y);
//  this->velocity = glm::normalize(targetPos - spawnOrigin) * speed;
//}
//
//void LinearProjectile::onUpdate()
//{
//  entity->position.x += velocity.x * Time::deltaTime();
//  entity->position.y += velocity.y * Time::deltaTime();
//
//  //check if out of range
//  float xDiff = entity->position.x - spawnOrigin.x;
//  float yDiff = entity->position.y - spawnOrigin.y;
//  float sqrdDistanceTravelled = (xDiff * xDiff) + (yDiff * yDiff);
//
//  if (sqrdDistanceTravelled > maxDistance * maxDistance)
//  {
//    entity->destroy();
//  }
//}
//
//void LinearProjectile::onCollisionHit(Entity& hit)
//{
//  if (hit.getCollisionLayer() == CollisionLayer::UNIT)
//  {
//    Unit& unitHit = static_cast<Unit&>(hit);
//
//    if (
//      (this->targetTeam == TARGET_TEAM_ENEMY && unitHit.getFaction() != casterFaction) ||
//      (this->targetTeam == TARGET_TEAM_FRIENDLY && unitHit.getFaction() == casterFaction) ||
//      (this->targetTeam == TARGET_TEAM_BOTH)
//      )
//    {
//      onProjectileHit(unitHit);
//
//      if (destroyOnHit)
//      {
//        entity->destroy();
//      }
//    }
//  }
//}
//
//void LinearProjectile::onProjectileHit(Unit& unitHit)
//{
//  DamageData data;
//  data.amount = damage;
//  data.victimID = unitHit.getID();
//  data.attackerID = casterID;
//  applyDamage(data);
//}