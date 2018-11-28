#include "cast_abiltiys.h"
#include "../unit.h"
#include <debug.h>

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
    glm::vec3 casterPos = getCasterPosition();
    ability->cast();
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