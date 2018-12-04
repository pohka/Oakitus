#include "unit.h"
#include <debug.h>
#include <core/time.h>
#include "player.h"
#include "ability.h"
#include "gFallback.h"
#include <fallback.h>

using namespace game;

const float Unit::BASE_MOVE_SPEED = 400.0f;

Unit::Unit()
{
  owner = &gFallback::player;
  moveSpeed = BASE_MOVE_SPEED;
  collisionLayer = oak::CollisionLayer::UNIT;
  faction = FACTION_NONE;
  health = 100;
  animator = &oak::Fallback::animator;
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

oak::BasePlayer& Unit::getOwner() const
{
  return *owner;
}

bool Unit::isOwnerBotPlayer() const
{
  return m_isOwnerBotPlayer;
}


bool Unit::hasOwner() const
{
  return m_hasOwner;
}

float Unit::getMoveSpeed() const
{
  return moveSpeed;
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
      abil->onAbilityStart();
      abil->setCastState(CAST_STATE_CASTING);
    }
    if (abil->getCastState() == CAST_STATE_CASTING && now >= abil->getEndTime())
    {
      abil->onAbilityEnd();
      abil->setCastState(CAST_STATE_NONE);
    }
  }
}

uchar Unit::getFaction() const
{
  return faction;
}

int Unit::getHealth() const
{
  return health;
}
void Unit::setHealth(int hp)
{
  health = hp;
}

void Unit::applyDamage(int amount, uint attackerID, uint abilityID)
{
  if (isAlive())
  {
    this->health -= amount;
    LOG << "health :" << health;
    if (health <= 0)
    {
      health = 0;
      onDeath();
    }
  }
}

bool Unit::isAlive() const
{
  return health > 0;
}

void Unit::onDeath()
{
  LOG << "onDeath()";
  destroy();
  //notify components
  //then do something
}

void Unit::addAnimator(oak::Animator* animator)
{
  m_hasAnimator = true;
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