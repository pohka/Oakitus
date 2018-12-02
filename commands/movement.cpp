#include "movement.h"
#include <debug.h>

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
  float axisX = 0.0f;
  float axisY = 0.0f;

  if (Input::isKeyPressed(KeyCode::W))
  {
    axisY += 1.0f;
  }
  if (Input::isKeyPressed(KeyCode::S))
  {
    axisY -= 1.0f;
  }
  if (Input::isKeyPressed(KeyCode::A))
  {
    axisX -= 1.0f;
  }
  if (Input::isKeyPressed(KeyCode::D))
  {
    axisX += 1.0f;
  }

  Unit* unit = player->getAssignedUnit();

  //if has input
  if (axisX != 0.0f || axisY != 0.0f)
  {
    float speed = unit->getMoveSpeed() * Time::deltaTime;

    unit->position.x += speed * axisX;
    unit->position.y += speed * axisY;

    unit->setAnimation(ANIM_TYPE_RUN);
  }
  else
  {
    unit->setAnimation(ANIM_TYPE_IDLE);
  }
}
