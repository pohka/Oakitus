#include <oak/components/unit.h>
#include <oak/oak_def.h>
#include <cmath>
#include <oak/debug.h>
#include <oak/core/fmath.h>

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
  if (isAlive)
  {
    updateCastingState();

    //update modifiers
  }

  for (auto abil : abilitys)
  {
    abil->updateCooldownEndTime(Time::deltaTime());
  }
}

void Unit::updateCastingState()
{
  //move between casting states
  if (
    castingState == CASTING_STATE_PRECAST &&
    Time::getGameTime() >= spellStartTime + curAbilityCasting->getPreCastTime()
    )
  {
    //if unit still has enough mana once the spell starts
    if (curAbilityCasting->getManaCost() <= mana)
    {
      curAbilityCasting->setCooldownEndTime();
      mana -= curAbilityCasting->getManaCost();
      curAbilityCasting->onSpellStart();
      castingState = CASTING_STATE_CASTING;
    }
    else
    {
      castingState = CASTING_STATE_NONE;
    }
  }
  if (
    castingState == CASTING_STATE_CASTING &&
    Time::getGameTime() >= spellEndTime
    )
  {
    castingState = CASTING_STATE_NONE;
  }
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

void Unit::setMana(const int mana)
{
  this->mana = FMath::clamp(mana, 0, maxMana);
}

void Unit::setHealth(const int health)
{
  this->health = FMath::clamp(health, 0, maxHealth);
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
  //currently casting another ability
  if (castingState != CASTING_STATE_NONE)
  {
    return;
  }

  if (index >= abilitys.size())
  {
    curAbilityCasting = nullptr;
    LOG_WARNING << "ability not found at index: " << index;
    return;
  }
  curAbilityCasting = abilitys[index];

  //if not enough mana
  if (curAbilityCasting->getManaCost() > mana)
  {
    //todo: not enough mana notification to player
    return;
  }

  if (curAbilityCasting->isOffCooldown() == false)
  {
    //todo: on cooldown notification to player
    return;
  }


  spellStartTime = Time::getGameTime();
  spellEndTime = Time::getGameTime() + curAbilityCasting->getPreCastTime() + curAbilityCasting->getDuration();
  curAbilityCasting->onSpellCast();
  castingState = CASTING_STATE_PRECAST;
  updateCastingState();
}


uint Unit::getAbilityCount() const
{
  return abilitys.size();
}

void Unit::addAbility(Ability* ability)
{
  ability->setOwner(this);
  abilitys.push_back(ability);
}

void Unit::giveMana(const int amount)
{
  float nextMana = this->mana + amount;
  this->mana = FMath::clamp(nextMana, 0, maxMana);
}

void Unit::heal(const int amount)
{
  float nextHP = this->health + amount;
  this->health = FMath::clamp(nextHP, 0, maxHealth);
}
