#ifndef E_DEATH_H
#define E_DEATH_H

#include <event/event.h>
#include "../game_def.h"

namespace game
{
  //typedef
  class DeathListener;
  struct DeathData;
  typedef oak::Event<DeathListener, DeathData> DeathEvent;


  //event data
  struct DeathData : public oak::IEventData
  {
    int victimID;
    int killerID;
  };

  static uint deathListenerIDCount = 0;

   //listener interface
  class DeathListener
  {
    uint listenerID;
    
  public:
    
    DeathListener()
    {
      oak::addEventListener<DeathEvent, DeathListener>(EVENT_ON_DEATH, this);
    }
    ~DeathListener()
    {
      oak::removeEventListener<DeathEvent, DeathListener>(EVENT_ON_DEATH, listenerID);
    }

    

    uint getListenerID()
    {
      return listenerID;
    }

    virtual void onDeath(DeathData& data) = 0;
  };
  

  //onFire callback function
  template <typename Listener, typename Data>
  void  onDeathFire(Listener* listener, Data& data)
  {
    listener->onDeath(data);
  }
}

#endif