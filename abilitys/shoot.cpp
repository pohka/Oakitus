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

void Shoot::cast(float x, float y)
{
  LOG << "casting";
  Arrow* arrow = new Arrow(x, y);
  arrow->instantiate();
}