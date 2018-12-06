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
  typedef oak::BaseListener<DeathEvent, DeathListener> BaseDeathListener;

  //event data
  struct DeathData : public oak::IEventData
  {
    int victimID;
    int killerID;
  };

  class DeathListener : public BaseDeathListener
  {
    public:
      DeathListener(const uchar eventID = EVENT_ON_DEATH) : 
        BaseDeathListener(eventID)
      {}
      ~DeathListener() {}
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