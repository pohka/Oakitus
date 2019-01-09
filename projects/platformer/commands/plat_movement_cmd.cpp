#include "plat_movement_cmd.h"
#include "../plat_consts.h"
#include "../prefabs/a_player.h"
#include <oak/collision/physics.h>

using namespace oak;
using namespace plat;

plat::MovementCMD::MovementCMD() : Command(COMMAND_MOVEMENT)
{
}

void plat::MovementCMD::execute()
{

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


  APlayer* actor = static_cast<APlayer*>(player->getAssignedActor());
  
  glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f);

  translate.x += axisX * speed * Time::deltaTime();

  if (actor->state == APlayer::STATE_AIR)
  {
    translate.y -= gravity * Time::deltaTime();
  }

  bool hasMoved = true;

  //update animation
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

  

  RaycastHit2D hit;
  bool hasHit = Physics::Raycast2D(
    actor->transform->position2D(),// - glm::vec2(70.0f, 0.0f),
    glm::vec2(-1.0f, 0.0f), 
    hit, 
    100.0f,
    COLLISION_LAYER_ALL
  );
  if (hasHit)
  {
    LOG << "hit dist:" << hit.distance << " (" << hit.point.x << "," << hit.point.y << ") " << hit.entityHit->name;
  }

  //apply change in position
  actor->transform->moveBy(translate);
}