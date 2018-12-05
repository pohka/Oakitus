#include "cast_abiltiys.h"
#include "../unit.h"
#include <debug.h>
#include <core/camera.h>
#include "../ability.h"

using namespace game;
using namespace oak;
using namespace game::command;



CastAbilitys::CastAbilitys(Player& player)
{
  this->player = &player;
}

CastAbilitys::~CastAbilitys()
{

}

void CastAbilitys::execute()
{
  if (Input::isKeyDown(KeyCode::Q))
  {
    beginCast(0);
  }

  if (Input::isKeyDown(KeyCode::E))
  {
    beginCast(1);
  }

  if (Input::isKeyDown(KeyCode::SPACE))
  {
    beginCast(2);
  }
  if (Input::isKeyDown(KeyCode::R))
  {
    beginCast(3);
  }
}

glm::vec3 CastAbilitys::getCasterPosition() const
{
  Unit* unit = player->getAssignedUnit();
  if (unit == nullptr)
  {
    LOG_WARNING << "UNIT NOT FOUND";
    return glm::vec3(0, 0, 0);
  }

  return unit->position;
}

void CastAbilitys::beginCast(const int index) const
{
  Unit* unit = player->getAssignedUnit();
  Ability* ability = unit->getAbilityByIndex(index);
  if (ability != nullptr)
  {
    if (ability->getTargetType() == TARGET_TYPE_POINT)
    {
      glm::vec2 point = Camera::cursorToWorld2D();
      ability->castOnPoint(point);
    }
    else if (ability->getTargetType() == TARGET_TYPE_NO_TARGET)
    {
      //glm::vec2 target = Camera::cursorToWorld2D();
      ability->castNoTarget();
    }
  }
}