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
    Unit* unit = player->getAssignedUnit();
    Ability* ability = unit->getAbilityByIndex(0);

    if (ability->getTargetType() == TargetType::POINT)
    {
      glm::vec2 point = Camera::cursorToWorld2D();
      ability->castOnPoint(point);
    }
    else if (ability->getTargetType() == TargetType::NO_TARGET)
    {
      //glm::vec2 target = Camera::cursorToWorld2D();
      ability->castNoTarget();
    }

    //glm::vec3 casterPos = getCasterPosition();
    //ability->cast();
  }
}

glm::vec3 CastAbilitys::getCasterPosition() const
{
  
  Unit* unit = player->getAssignedUnit();
  if (unit == nullptr)
  {
    LOG << "UNIT NOT FOUND";
    return glm::vec3(0, 0, 0);
  }

  return unit->position;
}