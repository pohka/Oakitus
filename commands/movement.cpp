#include "movement.h"
#include <debug.h>
#include <oak_def.h>

using namespace oak;
using namespace game;
using namespace game::command;

Movement::Movement(Player& player)
{
  this->player = &player;
}

Movement::~Movement()
{

}

void Movement::execute()
{
  Unit* unit = player->getAssignedUnit();
  if (unit == nullptr || !unit->isAlive())
  {
    return;
  }

  float axisX = 0.0f;
  float axisY = 0.0f;

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

  

  //if has input
  if (axisX != 0.0f || axisY != 0.0f)
  {
    float speed = unit->getMoveSpeed() * Time::deltaTime();

    unit->position.x += speed * axisX;
    unit->position.y += speed * axisY;

    //flip direction if required
    if (axisX > 0.0f && unit->getAnimDirection() != ANIM_DIRECTION_RIGHT)
    {
      unit->setAnimDirection(ANIM_DIRECTION_RIGHT);
      LOG << "DIRECTION RIGHT";
    }
    else if (axisX < 0.0f && unit->getAnimDirection() != ANIM_DIRECTION_LEFT)
    {
      unit->setAnimDirection(ANIM_DIRECTION_LEFT);
      LOG << "DIRECTION LEFT";
    }

    unit->setAnimation(ANIM_TYPE_RUN);

  }
  else
  {
    unit->setAnimation(ANIM_TYPE_IDLE);
  }
}
