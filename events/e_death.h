#ifndef E_DEATH_H
#define E_DEATH_H

#include <event/event.h>
#include <event/event_data.h>
#include "../game_def.h"

namespace game
{
  struct DeathData : public oak::IEventData
  {
    int victimID;
    int killerID;
  };

  class DeathListener;
  typedef oak::CustomEvent<DeathListener, DeathData> DeathEvent;

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

  template <typename Listener, typename Data>
  void  onDeathFire(Listener* listener, Data& data)
  {
    listener->onDeath(data);
  }
}

#endif