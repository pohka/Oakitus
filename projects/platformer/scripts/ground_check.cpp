#include "ground_check.h"
#include <oak/oak.h>
#include "../prefabs/a_player.h"
#include "../reflect.h"

using namespace plat;
using namespace oak;

GroundCheck::GroundCheck() : Component(REFLECT_GROUND_CHECK, TICK_GROUP_AFTER_PHYSICS)
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
  
  bool isOnGround = unit->state == MOVE_STATE_ON_GROUND;

  //if changed state
  if (hasHit != isOnGround)
  {
    if (hasHit)
    {
      unit->onGroundTouch();
    }
    else if(!hasHit && isOnGround)
    {
      unit->state = MOVE_STATE_FALLING;
    }
  }
}