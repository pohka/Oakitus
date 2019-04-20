#include <oak/components/unit.h>
#include <oak/oak_def.h>
#include <cmath>

using namespace oak;

Unit::Unit(const std::string& name) : Component(REFLECT_UNIT, TICK_GROUP_DEFAULT, TICK_TYPE_TICKABLE, false)
{
  this->name = name;
}

Unit::~Unit()
{
  for (Ability* abil : abilitys)
  {
    delete abil;
  }
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

int Unit::getHealth() const
{
  return health;
}

int Unit::getMaxHealth() const
{
  return maxHealth;
}

int Unit::getMaxMana() const
{
  return maxMana;
}

int Unit::getMana() const
{
  return mana;
}

const std::string& Unit::getName() const
{
  return name;
}

void Unit::setMaxHealth(const int maxHealth)
{
  //current health should keep same percentage HP
  float fHP = (float)health * ((float)maxHealth / (float)this->maxHealth);
  //unit should not die if maxHP changes
  if (fHP < 1.0f && fHP > 0.0f)
  {
    health = 1;
  }
  else if(fHP > maxHealth)
  {
    health = maxHealth;
  }
  else
  {
    health = (int)round(fHP);
  }

  this->maxHealth = maxHealth;
}

void Unit::setMaxMana(const int maxMana)
{
  //current mana should keep same percentage mana/maxMana
  float fMP = (float)health * ((float)maxMana / (float)this->maxMana);
  if (fMP > maxMana)
  {
    mana = maxMana;
  }
  else
  {
    mana = (int)round(fMP);
  }

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

void Unit::castAbility(const uint index)
{
  if (abilitys.size() > index)
  {
    curAbilityCasting = abilitys[index];
  }
  else
  {
    curAbilityCasting = nullptr;
  }

  curAbilityCasting->onSpellCast();
  float preCastTime = curAbilityCasting->getPreCastTime();
  if (preCastTime <= 0.0f)
  {
    curAbilityCasting->onSpellStart();
  }
}


uint Unit::getAbilityCount() const
{
  return abilitys.size();
}

void Unit::addAbility(Ability* ability)
{
  abilitys.push_back(ability);
}