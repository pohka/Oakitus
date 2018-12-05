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
    public:
      EDamage(uchar eventID) : BaseEvent(eventID) {}

      void fire(int amount);
  };
}

#endif