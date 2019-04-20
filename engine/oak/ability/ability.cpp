#include <oak/ability/ability.h>

using namespace oak;

static unsigned int abilityCounter = 0;

Ability::Ability(const std::string& name) : name(name)
{
  abilityID = abilityCounter;
  abilityCounter++;
}

Ability::~Ability() {}

float Ability::getPreCastTime() const
{
  return preCastTime;
}

const std::string& Ability::getName() const
{
  return name;
}

unsigned int Ability::getAbilityID() const
{
  return abilityID;
}

float Ability::getPreCastTime()
{
  return preCastTime;
}