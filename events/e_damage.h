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

  class EDamage : public oak::Event
  {

    std::vector<DamageListener*> listeners;

    public:
      EDamage(uchar eventID = EVENT_ON_DAMAGE_TAKEN) : Event(eventID) {}

      void fire(oak::EventData& data);

      void addListener(DamageListener* listener);
  };
}

#endif