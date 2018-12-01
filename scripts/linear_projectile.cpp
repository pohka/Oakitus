#include "linear_projectile.h"
#include <oak.h>
#include "../unit.h"

using namespace game;
using namespace oak;

LinearProjectile::LinearProjectile(
  glm::vec2 targetPos,
  float speed,
  float maxDistance,
  bool destroyOnHit,
  uchar targetTeam,
  Faction casterFaction
)
{
  this->targetPos = targetPos;
  this->speed = speed;
  this->maxDistance = maxDistance;
  this->destroyOnHit = destroyOnHit;
  this->targetTeam = targetTeam;
  this->casterFaction = casterFaction;
}

LinearProjectile::~LinearProjectile()
{

}

void LinearProjectile::onStart()
{
  this->spawnOrigin = glm::vec2(entity->position.x, entity->position.y);
  this->velocity = glm::normalize(targetPos - spawnOrigin) * speed;
}

void LinearProjectile::onUpdate()
{
  entity->position.x += velocity.x * Time::deltaTime;
  entity->position.y += velocity.y * Time::deltaTime;

  //check if out of range
  float xDiff = entity->position.x - spawnOrigin.x;
  float yDiff = entity->position.y - spawnOrigin.y;
  float sqrdDistanceTravelled = (xDiff * xDiff) + (yDiff * yDiff);

  if (sqrdDistanceTravelled > maxDistance * maxDistance)
  {
    entity->destroy();
  }
}

void LinearProjectile::onCollisionHit(Entity& hit)
{
  if (hit.getCollisionLayer() == CollisionLayer::UNIT)
  {
    Unit* unitHit = static_cast<Unit*>(&hit);
    if(this->targetTeam == TARGET_TEAM_ENEMY && unitHit->getFaction() != casterFaction)
    {
      if (destroyOnHit)
      {
        entity->destroy();
      }
    }
    else if (this->targetTeam == TARGET_TEAM_FRIENDLY && unitHit->getFaction() == casterFaction)
    {
      if (destroyOnHit)
      {
        entity->destroy();
      }
    }
    if (this->targetTeam == TARGET_TEAM_BOTH)
    {
      if (destroyOnHit)
      {
        entity->destroy();
      }
    }
  }
}