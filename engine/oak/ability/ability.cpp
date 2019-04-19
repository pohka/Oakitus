#include <oak/ability/ability.h>

using namespace oak;

static unsigned int abilityCounter = 0;

Ability::Ability(const std::string& name)
{
  this->name = name;
  abilityID = abilityCounter;
  abilityCounter++;
}

Ability::~Ability() {}

float Ability::getPreCastTime() const
{
  return preCastTime;
}