#include "movement_cmd.h"
#include "sample_def.h"
#include "events/event_damage.h"
#include "scenes/game_scenes.h"

using namespace oak;
using namespace sample;

MovementCMD::MovementCMD() : Command(COMMAND_MOVEMENT) 
{
}

void MovementCMD::onTick()
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
    EventManager::triggerEvent<DamageEventData>(EVENT_DAMAGE, data);
  }

  if (Input::isKeyDown(KEYCODE_P))
  {
    SceneManager::setNextScene(new DemoScene());
  }
  else if (Input::isKeyDown(KEYCODE_O))
  {
    SceneManager::setNextScene(new DemoScene2());
  }

  bool hasMoved = (axisX != 0.0f || axisY != 0.0f);

  //Actor* actor = player->getAssignedActor();
  //if (actor != nullptr)
  //{
  //  Animator* animator = actor->getComponent<Animator>();

  //  if (animator != nullptr)
  //  {
  //    glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f);

  //    if (hasMoved)
  //    {
  //      //calculate the movement vector, so the actor moves at the same speed in all directions
  //      glm::vec2 move = glm::vec2(axisX, axisY);
  //      move = glm::normalize(move) * speed;

  //      translate.x += move.x * Time::deltaTime();
  //      translate.y += move.y * Time::deltaTime();
  //      //actor->position.x += move.x * Time::deltaTime();
  //      //actor->position.y += move.y * Time::deltaTime();

  //      if (axisX > 0.0f)
  //      {
  //        animator->setDirection(ANIM_DIRECTION_RIGHT);
  //      }
  //      else if (axisX < 0.0f)
  //      {
  //        animator->setDirection(ANIM_DIRECTION_LEFT);
  //      }

  //      animator->setAnim(ANIM_ACT_RUN);
  //    }
  //    else
  //    {
  //      animator->setAnim(ANIM_ACT_IDLE);
  //    }

  //    //translate.x *= Time::deltaTime();
  //    //translate.y *= Time::deltaTime();
  //    actor->transform->moveBy(translate);
  //  }
  //}
}