#include "projectile.h"
#include <oak.h>
//#include "../scripts/linear_projectile.h"
#include "../ability.h"
#include <debug.h>
#include "../global_funcs.h"


using namespace game::prefab;
using namespace oak;
using namespace game;

Projectile::Projectile(glm::vec2 targetPos, Unit& caster, uint abilityID)
{
  Sprite* sprite = new Sprite("face.png", 16.0f, 16.0f);
  addComponent(sprite);
  addCollision(new CollisionCircle(16.0f, 0.0f, 0.0f));


  this->targetPos = targetPos;
  damage = 20;
  speed = 150.0f;
  maxDistance = 1000.0f;
  destroyOnHit = true;
  targetTeam = TARGET_TEAM_ENEMY;
  casterFaction = caster.getFaction();
  this->abilityID = abilityID;
  casterID = caster.getID();

  this->collisionLayer = CollisionLayer::PROJECTILE;
}

Projectile::~Projectile()
{
  
}

void Projectile::onStart()
{
  spawnOrigin = glm::vec2(position.x, position.y);
  velocity = glm::normalize(targetPos - spawnOrigin) * speed;
}

void Projectile::onUpdate()
{
  position.x += velocity.x * Time::deltaTime();
  position.y += velocity.y * Time::deltaTime();

  //check if out of range
  float xDiff = position.x - spawnOrigin.x;
  float yDiff = position.y - spawnOrigin.y;
  float sqrdDistanceTravelled = (xDiff * xDiff) + (yDiff * yDiff);

  if (sqrdDistanceTravelled > maxDistance * maxDistance)
  {
    destroy();
  }
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
  DamageData data;
  data.amount = damage;
  data.victimID = unitHit.getID();
  data.attackerID = casterID;
  applyDamage(data);
}