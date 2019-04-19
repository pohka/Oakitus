#include <oak/components/unit.h>
#include <oak/oak_def.h>

using namespace oak;

Unit::Unit(const std::string& name) : Component(REFLECT_UNIT, TICK_GROUP_DEFAULT, TICK_TYPE_TICKABLE, false)
{
  this->name = name;
}

Unit::~Unit()
{

}

void Unit::onCreate()
{
  this->level = startingLevel;
}

void Unit::onTick()
{
  //update modifiers
}


bool Unit::getIsAlive() const
{
  return isAlive;
}

float Unit::getHealth() const
{
  return health;
}

float Unit::getMaxHealth() const
{
  return maxHealth;
}

float Unit::getMaxMana() const
{
  return maxMana;
}

float Unit::getMana() const
{
  return mana;
}

const std::string& Unit::getName() const
{
  return name;
}

void Unit::setMaxHealth(float maxHealth)
{
  this->maxHealth = maxHealth;
}

void Unit::setMaxMana(float maxMana)
{
  this->maxMana = maxMana;
}

void Unit::setStartingLevel(int level)
{
  this->startingLevel = level;
}

int Unit::getLevel() const
{
  return level;
}