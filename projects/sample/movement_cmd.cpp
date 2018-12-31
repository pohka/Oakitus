#include "movement_cmd.h"
#include <oak/core/time.h>

using namespace oak;
using namespace sample;

void MovementCMD::execute()
{
  const float speed = 100.0f;

  float x = 0.0f;
  float y = 0.0f;

  if (Input::isKeyPressed(KEYCODE_W))
  {
    y = speed;
  }
  if (Input::isKeyPressed(KEYCODE_S))
  {
    y = -speed;
  }
  if (Input::isKeyPressed(KEYCODE_A))
  {
    x = -speed;
  }
  if (Input::isKeyPressed(KEYCODE_D))
  {
    x = speed;
  }

  Actor* actor = player->getAssignedActor();
  if (actor != nullptr)
  {
    actor->position.x += x * Time::deltaTime();
    actor->position.y += y * Time::deltaTime();
  }
}