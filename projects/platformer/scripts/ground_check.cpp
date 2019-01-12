#include "ground_check.h"
#include <oak/oak.h>
#include "../prefabs/a_player.h"

using namespace plat;
using namespace oak;

GroundCheck::GroundCheck() : Component(TICK_GROUP_AFTER_PHYSICS)
{

}

void GroundCheck::onTick()
{
  //raycast the world to see if isOnGround state changed
  RaycastHit2D hit;
  uint layers = COLLISION_LAYER_WORLD;
  glm::vec2 pos = entity->transform->position2D();
  Unit* unit = static_cast<Unit*>(entity);
  float dist = unit->height * 0.5f;
  glm::vec2 down = glm::vec2(0.0f, -1.0f);

  bool hasHit = Physics::Raycast2D(pos, down, hit, dist, layers);
  
  //if changed state
  if (hasHit != unit->isOnGround)
  {
    unit->isOnGround = hasHit;
    if (unit->isPlayer && hasHit)
    {
      APlayer* aplayer = static_cast<APlayer*>(unit);
      aplayer->onGroundTouch();
    }
  }
}