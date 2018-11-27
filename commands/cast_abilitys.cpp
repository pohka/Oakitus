#include "cast_abiltiys.h"
#include "../unit.h"

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
    ability->cast(0,0);
  }
}