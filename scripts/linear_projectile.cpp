#include "linear_projectile.h"
#include <core/time.h>

using namespace game;
using namespace oak;

LinearProjectile::LinearProjectile(
  glm::vec2 spawnOrigin,
  glm::vec2 targetPos,
  float speed,
  float maxDistance,
  bool destroyOnHit
)
{
  this->spawnOrigin = spawnOrigin;
  this->velocity = glm::normalize(targetPos - spawnOrigin) * speed;
  this->maxDistance = maxDistance;
  this->destroyOnHit = destroyOnHit;
}

LinearProjectile::~LinearProjectile()
{

}

void LinearProjectile::onStart()
{
  entity->position.x = spawnOrigin.x;
  entity->position.y = spawnOrigin.y;
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