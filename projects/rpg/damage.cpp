#include "damage.h"

using namespace game;

void Damage::calcTotalAmount(game::DamageData& damage)
{
  damage.totalAmount = damage.amount;
  Unit* caster = Unit::findUnit(damage.casterID);
  if (caster != nullptr)
  {
    auto& modifiers = caster->getAllModifiers();

    int damageAmp = 0;
    float ampExtra = 0;
    uchar ampPropID = MODIFIER_PROP_AMP_NORMAL + damage.element;
    uchar damagePropID = MODIFIER_PROP_NORMAL_DAMAGE + damage.element;
    uchar foundCount = 0;

    //find all the amp and damage props for each modifier with the matching element type
    for (uint i = 0; i < modifiers.size(); i++)
    {
      foundCount = 0;

      //find modifier by prop
      for (auto it = modifiers[i]->props.begin(); it != modifiers[i]->props.end() && foundCount < 2; ++it)
      {
        //flat damage
        if (it->first == damagePropID)
        {
          damage.totalAmount += (float)it->second;
          foundCount++;
        }
        //percentage damage
        else if (it->first == ampPropID)
        {
          damageAmp += it->second;
          foundCount++;
        }
      }
    }

    //apply percentage after all modifier flat damage
    damage.totalAmount += damage.totalAmount * ((float)damageAmp / 100.0f);
  }
}


int Damage::calcAfterReductions(Unit* victim, DamageData& damage)
{
  auto modifiers = victim->getAllModifiers();
  int modifierResist = 0;
  for (uint i = 0; i < modifiers.size(); i++)
  {
    auto& props = modifiers[i]->props;
    uchar propID = MODIFIER_PROP_RESIST_NORMAL + damage.element;
    if (props.find(propID) != props.end())
    {
      modifierResist += modifiers[i]->props[propID];
    }
  }
  float multiplier = (float)(100 - victim->getResist(damage.element) - modifierResist) / 100.0f;
  return (int)(damage.totalAmount * multiplier);
}


void Damage::apply(game::DamageData& rawDamage)
{
  calcTotalAmount(rawDamage);
  oak::IEvent* event = oak::EventManager::getEvent(EVENT_ON_DAMAGE_TAKEN);
  event->fire(rawDamage);
}

void Damage::apply(float amount, uchar element, uint casterID, uint victimID)
{
  game::DamageData damage;
  damage.amount = amount;
  damage.element = element;
  damage.casterID = casterID;
  damage.victimID = victimID;
  apply(damage);
}