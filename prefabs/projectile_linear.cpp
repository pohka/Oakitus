#include "projectile_linear.h"


using namespace game;
using namespace game::prefab;

ProjectileLinear::ProjectileLinear(glm::vec2 targetPos,
  Unit& caster,
  uint abilityID,
  DamageData damage,
  float speed,
  float radius,
  float maxDistance,
  bool destroyOnHit,
  uchar targetTeam) :
    Projectile(
      targetPos,
      caster,
      abilityID,
      damage,
      speed,
      radius,
      destroyOnHit,
      targetTeam
    )
{
  this->maxDistance = maxDistance;
}

void ProjectileLinear::onStart()
{
  spawnOrigin = glm::vec2(position.x, position.y);
  velocity = glm::normalize(targetPos - spawnOrigin) * speed;
}

void ProjectileLinear::onUpdate()
{
  position.x += velocity.x * oak::Time::deltaTime();
  position.y += velocity.y * oak::Time::deltaTime();

  //check if out of range
  float xDiff = position.x - spawnOrigin.x;
  float yDiff = position.y - spawnOrigin.y;
  float sqrdDistanceTravelled = (xDiff * xDiff) + (yDiff * yDiff);

  if (sqrdDistanceTravelled > maxDistance * maxDistance)
  {
    destroy();
  }
}