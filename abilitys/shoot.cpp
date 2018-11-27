#include "shoot.h"
#include  <core/debug.h>
#include "../prefabs/arrow.h"

using namespace game::ability;

Shoot::Shoot()
{

}

Shoot::~Shoot()
{

}

void Shoot::cast()
{
  LOG << "casting";
  prefab::Arrow* arrow = new prefab::Arrow();
  arrow->instantiate(caster->position.x, caster->position.y);
}