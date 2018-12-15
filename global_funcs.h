#ifndef GLOBAL_FUNCS_H
#define GLOBAL_FUCHS_H

#include "events/e_damage_taken.h"
#include <event/event_manager.h>

namespace game
{

  Unit* findUnit(uint entityID)
  {
    return static_cast<Unit*>(oak::Entity::findEntityByID(entityID));
  }

  //convert from raw damage to damage after modifiers. usign the attackerID
  void applyDamageModifiers(game::DamageData& data)
  {
    Unit* attacker = findUnit(data.attackerID);
    if (attacker != nullptr)
    {
      auto modifiers = attacker->getAllModifiers();
      for (uint i = 0; i < modifiers.size(); i++)
      {
        for (auto it = modifiers[i]->properties.begin(); it != modifiers[i]->properties.end(); ++it)
        {
          if (it->first == MODIFIER_NORMAL_DAMAGE)
          {
            data.amount += it->second;
          }
        }
      }
    }
  }

  ///apply damage to a unit with damage data
  void applyDamage(game::DamageData& data)
  {
    applyDamageModifiers(data);
    oak::IEvent* event = oak::EventManager::getEvent(EVENT_ON_DAMAGE_TAKEN);
    event->fire(data);
  }

}

#endif