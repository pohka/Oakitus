#include "shoot.h"
#include "../prefabs/arrow.h"
#include <debug.h>

using namespace game::ability;

Shoot::Shoot()
{
  targetType = TargetType::POINT;
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
  
}

void Shoot::onAbilityStart()
{
  //LOG << "onAbilityStart()";
  prefab::Arrow* arrow = new prefab::Arrow(target.point);
  arrow->instantiate(caster->position.x, caster->position.y);
}

void Shoot::onAbilityEnd()
{
 //LOG << "onAbilityEnd()";
}