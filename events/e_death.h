#ifndef E_DEATH_H
#define E_DEATH_H

#include <event/event.h>
#include <event/event_data.h>
#include <vector>
#include "../game_def.h"



namespace game
{

  template <typename Listener, typename Data>
  void deathonFire(Listener* listener, Data& data)
  {
    listener->onDeath(data);
  }

  template <typename Listener, typename Data>
  class EGeneric : public oak::Event
  {
    std::vector<Listener*> listeners;
    void(*onFire)(Listener*, Data&);

  public:
    EGeneric(uchar eventID, void(*onFire)(Listener*, Data&)) : Event(eventID) 
    {
      this->onFire = onFire;
    }

    void fire(oak::EventData& data) override
    {
      Data& customData = static_cast<Data&>(data);

      for (uint i = 0; i < listeners.size(); i++)
      {
        onFire(listeners[i], customData);
      }
    }

    void addListener(Listener* listener)
    {
      listeners.push_back(listener);
    }
  };


  struct DeathData : public oak::EventData
  {
    int victimID;
    int killerID;
  };

  class DeathListener;
  typedef EGeneric<DeathListener, DeathData> DeathEvent;

   //listener interface
  class DeathListener
  {
  public:
    DeathListener()
    {
      oak::addEventListener<DeathEvent, DeathListener>(EVENT_ON_DEATH, this);
    }
    virtual void onDeath(DeathData& data) = 0;
  };
}

#endif