#include "movement_cmd.h"
#include <oak/core/time.h>
#include <oak/components/animator.h>
#include "sample_def.h"
#include <oak/event/event_manager.h>
#include "events/event_damage.h"

using namespace oak;
using namespace sample;

void MovementCMD::execute()
{
  const float speed = 100.0f;

  float axisX = 0.0f;
  float axisY = 0.0f;

  
  //directional input
  if (Input::isKeyPressed(KEYCODE_W))
  {
    axisY += 1.0f;
  }
  if (Input::isKeyPressed(KEYCODE_S))
  {
    axisY -= 1.0f;
  }
  if (Input::isKeyPressed(KEYCODE_A))
  {
    axisX -= 1.0f;
  }
  if (Input::isKeyPressed(KEYCODE_D))
  {
    axisX += 1.0f;
  }

  if (Input::isKeyDown(KEYCODE_B))
  {
    DamageEventData data = { 10, 0, 1 };
    EventManager::triggerEvent<DamageEventData>(0, data);
  }

  bool hasMoved = (axisX != 0.0f || axisY != 0.0f);

  Actor* actor = player->getAssignedActor();
  if (actor != nullptr)
  {
    Animator* animator = actor->getComponent<Animator>();

    if (animator != nullptr)
    {
      if (hasMoved)
      {
        //calculate the movement vector, so the actor moves at the same speed in all directions
        glm::vec2 move = glm::vec2(axisX, axisY);
        move = glm::normalize(move) * speed;

        actor->position.x += move.x * Time::deltaTime();
        actor->position.y += move.y * Time::deltaTime();

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
  }
}