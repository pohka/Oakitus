#ifndef GLOBAL_FUNCS_H
#define GLOBAL_FUCHS_H

#include "events/e_damage_taken.h"
#include <event/event_manager.h>

namespace game
{
  ///apply damage to a unit with damage data
  void applyDamage(game::DamageData& data)
  {
    oak::IEvent* event = oak::EventManager::getEvent(EVENT_ON_DAMAGE_TAKEN);
    event->fire(data);
  }
}

#endif