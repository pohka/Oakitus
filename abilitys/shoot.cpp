#include "shoot.h"
#include "../prefabs/arrow.h"
#include <debug.h>

using namespace game::ability;

Shoot::Shoot()
{

}

Shoot::~Shoot()
{
  LOG << "Delocated shoot ability";
}

void Shoot::cast()
{
  LOG << "casting";
  prefab::Arrow* arrow = new prefab::Arrow();
  arrow->instantiate(caster->position.x, caster->position.y);
}