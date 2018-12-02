#include "shoot.h"
#include "../prefabs/arrow.h"
#include <debug.h>

using namespace game::ability;

Shoot::Shoot()
{
  targetType = TARGET_TYPE_POINT;
  preCastTime = 0.0f;
  castTime = 0.5f;
}

Shoot::~Shoot()
{
  LOG << "Delocated shoot ability";
}

void Shoot::onCast()
{
  //LOG << "onCast()";
  caster->setAnimation(ANIM_TYPE_ABILITY_1);
}

void Shoot::onAbilityStart()
{
  //LOG << "onAbilityStart()";
  prefab::Arrow* arrow = new prefab::Arrow(target.point, *caster, this->getID());
  arrow->instantiate(caster->position.x, caster->position.y);
}

void Shoot::onAbilityEnd()
{
 //LOG << "onAbilityEnd()";
}