#include "unit.h"
#include <debug.h>
#include <core/time.h>
#include "player.h"
#include "ability.h"
#include <fallback.h>
#include <event/event_manager.h>
#include <event/event.h>

using namespace game;

const float Unit::BASE_MOVE_SPEED = 400.0f;

Unit::Unit()
{
  EDamage();
  owner = nullptr;
  moveSpeed = BASE_MOVE_SPEED;
  collisionLayer = oak::CollisionLayer::UNIT;
  faction = FACTION_NONE;
  health = 100;
  animator = nullptr;

  oak::Event* event = oak::EventManager::getEvent(EVENT_ON_DAMAGE_TAKEN);
  EDamage* damageEvent = static_cast<EDamage*>(event);
  damageEvent->addListener(this);
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
  if (owner == nullptr)
  {
    LOG_WARNING << "Unit '" << name << "' does not have an owner";
  }
  return owner;
}

bool Unit::isOwnerBotPlayer() const
{
  return m_isOwnerBotPlayer;
}


bool Unit::hasOwner() const
{
  return (owner != nullptr);
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
      
     //onDeath();
    }
  }
}

bool Unit::isAlive() const
{
  return health > 0;
}

void Unit::onDamageTaken(DamageData& data)
{
  LOG << "onDamageTaken() " << data.amount;
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