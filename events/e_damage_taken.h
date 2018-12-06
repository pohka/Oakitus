#ifndef E_DAMAGE_TAKEN_H
#define E_DAMAGE_TAKEN_H

#include <event/event.h>
#include "../game_def.h"

namespace game
{
  //typedef
  class DamageTakenListener;
  struct DamageTakenData;
  typedef oak::Event<DamageTakenListener, DamageTakenData> DamageTakenEvent;
  typedef oak::BaseListener<DamageTakenEvent, DamageTakenListener> BaseDamageTakenListener;

  //event data
  struct DamageTakenData : public oak::IEventData
  {
    int amount;
    int victimID;
    int attackerID;
  };

  class DamageTakenListener : public BaseDamageTakenListener
  {
  public:
    DamageTakenListener(const uchar eventID = EVENT_ON_DAMAGE_TAKEN) :
      BaseDamageTakenListener(eventID)
    {}
    ~DamageTakenListener() {}
    virtual void onDamageTaken(DamageTakenData& data) = 0;
  };


  //onFire callback function
  template <typename Listener, typename Data>
  void  onDamageTakenFire(Listener* listener, Data& data)
  {
    listener->onDamageTaken(data);
  }
}

#endif