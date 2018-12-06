#ifndef E_DAMAGE_H
#define E_DAMAGE_H

#include <event/event.h>
#include <event/event_data.h>
#include <vector>
#include "damage_listener.h"
#include "damage_data.h"
#include "../game_def.h"

namespace game
{

  class EDamage : public oak::IEvent
  {

    std::vector<DamageListener*> listeners;

    public:
      EDamage(uchar eventID = EVENT_ON_DAMAGE_TAKEN) : IEvent(eventID) {}

      void fire(oak::IEventData& data);

      void addListener(DamageListener* listener);
  };
}

#endif