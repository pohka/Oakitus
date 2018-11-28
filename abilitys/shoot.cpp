#include "shoot.h"
#include "../prefabs/arrow.h"
#include <debug.h>

using namespace game::ability;

Shoot::Shoot()
{
  targetType = TargetType::POINT;
}

Shoot::~Shoot()
{
  LOG << "Delocated shoot ability";
}

void Shoot::onCast()
{
  LOG << "onCast()";
  prefab::Arrow* arrow = new prefab::Arrow(target.point);
  arrow->instantiate(caster->position.x, caster->position.y);
}