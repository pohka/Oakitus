#ifndef E_DEATH_H
#define E_DEATH_H

#include <event/event.h>
#include <event/event_data.h>
#include <vector>
#include "../game_def.h"

namespace game
{
  //event data to be passed to the listenr
  struct DeathData : public oak::EventData
  {
    int victimID;
    int killerID;
  };

  class EDeath;

  //listener interface
  class DeathListener
  {
    public:
      DeathListener()
      {
        oak::addEventListener<EDeath,DeathListener>(EVENT_ON_DEATH, this);
      }
      virtual void onDeath(DeathData& data) = 0;
  };

  //event
  class EDeath: public oak::Event
  {
    std::vector<DeathListener*> listeners;

    public:
      EDeath(uchar eventID = EVENT_ON_DEATH) : Event(eventID) {}

      void fire(oak::EventData& data)
      {
        DeathData& deathData = static_cast<DeathData&>(data);

        for (uint i = 0; i < listeners.size(); i++)
        {
          listeners[i]->onDeath(deathData);
        }
      }

      void addListener(DeathListener* listener)
      {
        listeners.push_back(listener);
      }
  };

}

#endif