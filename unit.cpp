#include "unit.h"
#include <debug.h>
#include <core/time.h>
#include "player.h"
#include "ability.h"
#include <fallback.h>
#include <event/event_manager.h>
#include <event/event.h>
#include <core/player_resource.h>
#include <ui/ui_canvas.h>
#include "damage.h"

using namespace game;

Unit::Unit()
{
  collisionLayer = oak::CollisionLayer::UNIT;
  animator = nullptr;
}

Unit::~Unit()
{
  while (!abilitys.empty())
  {
    delete abilitys[0];
    abilitys.erase(abilitys.begin());
  }

  LOG << "deallocated unit: " << name;
}

void Unit::onStart()
{
  if (animator == nullptr)
  {
    LOG_WARNING << "Unit '" << name << "' does not have an animator, use addAnimator() ";
  }
}

oak::BasePlayer* Unit::getOwner() const
{
  if (!m_hasOwner)
  {
    LOG_WARNING << "Unit '" << name << "' does not have an owner";
  }
  return &oak::PlayerResource::getPlayer(ownerID);
}

bool Unit::isOwnerBotPlayer() const
{
  return m_isOwnerBotPlayer;
}

void Unit::setOwner(uint playerID)
{
  ownerID = playerID;
  m_hasOwner = true;
}

void Unit::removeOwner()
{
  m_hasOwner = false;
}

bool Unit::hasOwner() const
{
  return m_hasOwner;
}

int Unit::getMoveSpeed() const
{
  int totalMoveSpeed = moveSpeed;
  for (Modifier* modifier : modifiers)
  {
    for (auto it = modifier->props.begin(); it != modifier->props.end(); ++it)
    {
      if (it->first == MODIFIER_PROP_MOVESPEED)
      {
        totalMoveSpeed += it->second;
        break;
      }
    }
  }

  if (totalMoveSpeed < 0)
  {
    totalMoveSpeed = 0;
  }

  return totalMoveSpeed;
}

void Unit::setMoveSpeed(float moveSpeed)
{
  this->moveSpeed = moveSpeed;
}

void Unit::addAbility(Ability* ability)
{
  ability->caster = this;
  abilitys.push_back(ability);
}

Ability* Unit::getAbilityByIndex(uint index) const
{
  if (index >= abilitys.size())
  {
    LOG_WARNING << "Unit '" << name << "' does not have an ability at index: " << index;
    return nullptr;
  }
  return abilitys[index];
}

void Unit::onUpdate()
{
  Entity::onUpdate();
  float now = oak::Time::getTimeNow();

  //update ability casting states
  for (Ability* abil : abilitys)
  {
    if (abil->getCastState() == CAST_STATE_PRECAST && now >= abil->getStartTime())
    {
      useMana(abil->getManaCost());
      abil->onAbilityStart();
      abil->setCastState(CAST_STATE_CASTING);
    }
    if (abil->getCastState() == CAST_STATE_CASTING && now >= abil->getEndTime())
    {
      abil->onAbilityEnd();
      abil->setCastState(CAST_STATE_NONE);
    }
  }

  for (uint i=0; i<modifiers.size(); i++)
  {
    modifiers[i]->onUpdate();

    if (modifiers[i]->destroyOnExpire && now >= modifiers[i]->getEndTime())
    {
      modifiers[i]->onDestroy();
      delete modifiers[i];
      modifiers.erase(modifiers.begin() + i);
      i--;
    }
  }
}

uchar Unit::getFaction() const
{
  return faction;
}

int Unit::getHealth() const
{
  int totalHealth = health;
  for (Modifier* modifier : modifiers)
  {
    for (auto it = modifier->props.begin(); it != modifier->props.end(); ++it)
    {
      if (it->first == MODIFIER_PROP_HEALTH)
      {
        totalHealth += it->second;
        break;
      }
    }
  }

  return totalHealth;
}
void Unit::setHealth(int hp)
{
  health = hp;
}

bool Unit::isAlive() const
{
  return health > 0;
}

void Unit::onDamageTaken(DamageData& data)
{
  if (isAlive() && data.victimID == getID())
  {
    this->health -= Damage::calcAfterReductions(this, data);

    LOG << "health :" << health;
    if (health <= 0)
    {
      health = 0;

      DeathData deathData;
      deathData.killerID = data.casterID;
      deathData.victimID = this->getID();
      oak::EventManager::getEvent(EVENT_ON_DEATH)->fire(deathData);
    }
  }
}

void Unit::onDeath(DeathData& data)
{
  if (data.victimID == getID())
  {
    LOG << "onDeath()";
    for (Modifier* modifier : modifiers)
    {
      modifier->onDeath();
    }

    destroy();

  }
  //notify components
  //then do something
}

void Unit::addAnimator(oak::Animator* animator)
{
  this->animator = animator;
  addComponent(animator);
}

void Unit::setAnimation(uchar animType)
{
  animator->setAnim(animType);
}

uchar Unit::getAnimDirection() const
{
  return animator->getDirection();
}

void Unit::setAnimDirection(uchar direction)
{
  animator->setDirection(direction);
}

void Unit::addModifier(uint casterID, Modifier* modifier)
{
  //check if has modifier
  for (uint i = 0; i < modifiers.size(); i++)
  {
    if (modifiers[i]->getModifierID() == modifier->getModifierID())
    {
      //if stackable, increment stack count
      if (modifier->isStackable && modifiers[i]->stackCount < modifiers[i]->maxStacks)
      {
        modifiers[i]->stackCount++;
      }
      //refresh
      else if (!modifier->isStackable)
      {
        modifiers[i]->refresh();
      }
      delete modifier;
      return;
    }
  }

  modifier->init(this, casterID);
  modifiers.push_back(modifier);
  modifier->onCreated();
}

void Unit::removeModifier(ushort modifierID, uint casterID)
{
  for (uint i = 0; i < modifiers.size(); i++)
  {
    if (modifiers[i]->getModifierID() == modifierID && modifiers[i]->casterID == casterID)
    {
      delete modifiers[i];
      modifiers.erase(modifiers.begin() + i);
      return;
    }
  }
}

std::vector<Modifier*>& Unit::getAllModifiers()
{
  return modifiers;
}

int Unit::getResist(uchar element)
{
  return resist[element];
}
int Unit::getAmplify(uchar element)
{
  return amplify[element];
}

Unit* Unit::findUnit(uint entityID)
{
  return static_cast<Unit*>(oak::Entity::findEntityByID(entityID));
}

int Unit::getMana()
{
  int totalMana = mana;
  for (Modifier* modifier : modifiers)
  {
    for (auto it = modifier->props.begin(); it != modifier->props.end(); ++it)
    {
      if (it->first == MODIFIER_PROP_MANA)
      {
        totalMana += it->second;
        break;
      }
    }
  }

  return totalMana;
}

void Unit::useMana(int amount)
{
  if (amount != 0)
  {
    mana -= amount;
    if (mana < 0)
    {
      mana = 0;
    }
  }
}