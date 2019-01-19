#include "movement.h"
#include <oak/oak.h>
#include "../prefabs/a_player.h"
#include "../plat_consts.h"

using namespace plat;
using namespace oak;


void Movement::applyMovement(float axisX, float axisY)
{
  Unit* unit = static_cast<Unit*>(entity);
  glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f);

  float multiplier = 1.0f;
  if (unit->state != MOVE_STATE_ON_GROUND)
  {
    multiplier = unit->airSpeedMultiplier;
  }

  //left and right movement
  translate.x += axisX * unit->speed * multiplier * Time::deltaTime();

  if (unit->state == MOVE_STATE_ON_GROUND)
  {
    if (Input::isKeyPressed(KEYCODE_SPACE))
    {
      translate.y += 100.0f;
    }
  }
  else
  {
    translate.y -= unit->gravity * Time::deltaTime();
  }

 
  bool hasMoved = true;  //placeholder

  //update animation
  Animator* animator = unit->getComponentWithReflection<Animator>(REFLECT_ANIMATOR);

  if (animator != nullptr)
  {
    if (hasMoved)
    {
      if (axisX > 0.0f)
      {
        animator->setDirection(ANIM_DIRECTION_RIGHT);
      }
      else if (axisX < 0.0f)
      {
        animator->setDirection(ANIM_DIRECTION_LEFT);
      }

      animator->setAnim(ANIM_ACT_RUN);
    }
    else
    {
      animator->setAnim(ANIM_ACT_IDLE);
    }
  }

  //apply change in position
  unit->transform->moveBy(translate);
  //Transform* transform = unit->getComponentWithReflection<Transform>(REFLECT_TRANSFORM);
  //transform->moveBy(translate);
}
