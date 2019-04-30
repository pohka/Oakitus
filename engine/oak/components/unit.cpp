#include <oak/components/unit.h>
#include <oak/oak_def.h>
#include <cmath>
#include <oak/debug.h>
#include <oak/core/fmath.h>

using namespace oak;

Unit::Unit(const std::string& name) : 
  Component(
    Reflect::UNIT,
    Component::TickGroup::DEFAULT,
    TickType::TICKABLE,
    false
  )
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

void Unit::setMana(int mana)
{
  this->mana = FMath::clampInt(mana, 0, maxMana);
}

void Unit::setHealth(int health)
{
  this->health = FMath::clampInt(health, 0, maxHealth);
}

void Unit::setMaxHealth(int maxHealth)
{
  //current health should keep same percentage HP
  float fHP = static_cast<float>(health) * (static_cast<float>(maxHealth) / static_cast<float>(this->maxHealth));
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
    health = static_cast<int>(round(fHP));
  }

  this->maxHealth = maxHealth;
}

void Unit::setMaxMana(int maxMana)
{
  //current mana should keep same percentage mana/maxMana
  float fMP = static_cast<float>(health) * (static_cast<float>(maxMana) / static_cast<float>(this->maxMana));
  if (fMP > maxMana)
  {
    mana = maxMana;
  }
  else
  {
    mana = static_cast<int>(round(fMP));
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

void Unit::castAbility(uint index)
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

void Unit::giveMana(int amount)
{
  int nextMana = this->mana + amount;
  this->mana = FMath::clampInt(nextMana, 0, maxMana);
}
