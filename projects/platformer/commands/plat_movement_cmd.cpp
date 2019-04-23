#include "plat_movement_cmd.h"
#include "../plat_consts.h"
#include "../prefabs/a_player.h"
#include <oak/collision/physics.h>
#include "../scripts/movement.h"

using namespace oak;
using namespace plat;

plat::MovementCMD::MovementCMD() : Command(COMMAND_MOVEMENT)
{
}

void plat::MovementCMD::onTick()
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

  //Movement* movement = player->getAssignedActor()->getComponent<Movement>();
  //movement->applyMovement(axisX, axisY);
}