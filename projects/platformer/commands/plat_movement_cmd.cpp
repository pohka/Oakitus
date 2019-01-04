#include "plat_movement_cmd.h"
#include "../plat_consts.h"

using namespace oak;
using namespace plat;

plat::MovementCMD::MovementCMD() : Command(COMMAND_MOVEMENT)
{
}

void plat::MovementCMD::execute()
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

  bool hasMoved = (axisX != 0.0f || axisY != 0.0f);

  Actor* actor = player->getAssignedActor();

  if (actor != nullptr)
  {
    if (hasMoved)
    {
      //calculate the movement vector, so the actor moves at the same speed in all directions
      glm::vec2 move = glm::vec2(axisX, axisY);
      move = glm::normalize(move) * speed;

      actor->position.x += move.x * Time::deltaTime();
      actor->position.y += move.y * Time::deltaTime();
    }

    Animator* animator = actor->getComponent<Animator>();

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
  }
}