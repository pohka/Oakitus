#ifndef E_DAMAGE_H
#define E_DAMAGE_H

#include <event/event_manager.h>
#include <event/base_event.h>
#include "damage_listener.h"
#include <debug.h>

namespace game
{
  class EDamage : public oak::BaseEvent
  {
    std::vector<DamageListener*> listeners;

  public:
    EDamage(uchar eventID, int amount) : BaseEvent(eventID)
    {

    }

    void addListener(DamageListener* listener)
    {
      listeners.push_back(listener);
    }

    void fire(int amount)
    {
      for (uint i = 0; i < listeners.size(); i++)
      {
        listeners[i]->onFire(amount);
      }
    }
  };
}

#endif