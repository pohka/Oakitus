#include <oak/ability/ability.h>
#include <oak/core/types.h>

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

void Ability::setOwner(Unit* unit)
{
  owner = unit;
}

void Ability::levelUp()
{
  if (currentLevel < maxLevel)
  {
    currentLevel++;
  }
}

unsigned int Ability::getMaxLevel()
{
  return maxLevel;
}

unsigned int Ability::getLevel()
{
  return currentLevel;
}

int Ability::getManaCost() const
{
  //possible invalid level
  if (currentLevel == 0)
  {
    return manaCost[0];
  }
  //get by index
  else if (currentLevel - 1 < manaCost.size())
  {
    return manaCost[currentLevel - 1];
  }
  //no value for the current level, use the last value
  else
  {
    return manaCost[manaCost.size() - 1];
  }
}

float Ability::getCooldown() const
{
  //possible invalid level
  if (currentLevel == 0)
  {
    return cooldown[0];
  }
  //get by index
  else if (currentLevel - 1 < cooldown.size())
  {
    return cooldown[currentLevel - 1];
  }
  //no value for the current level, use the last value
  else
  {
    return cooldown[manaCost.size() - 1];
  }
}