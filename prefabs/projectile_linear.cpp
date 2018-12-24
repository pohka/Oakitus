#include "projectile_linear.h"
#include <glm/glm.hpp>
//#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

void ProjectileLinear::onCreate()
{
  Entity::onCreate();
  spawnOrigin = glm::vec2(position.x, position.y);
  velocity = glm::normalize(targetPos - spawnOrigin) * speed;

  //rotate projectile to face direction of velocity
  //animation should be drawn facing right
  glm::vec2 right = glm::vec2(1.0f, 0.0f);
  float dot = glm::dot(right, velocity); // dot product between[x1, y1] and [x2, y2]
  float det = right.x * velocity.y - right.y * velocity.x; // determinant
  float angle = atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)

  rotation.z = angle;
}

void ProjectileLinear::onUpdate()
{
  Entity::onUpdate();
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