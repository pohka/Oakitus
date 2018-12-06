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


  //event data
  struct DamageTakenData : public oak::IEventData
  {
    int amount;
    int victimID;
    int attackerID;
  };


  //listener interface
  class DamageTakenListener
  {
    uint listenerID;

  public:
    DamageTakenListener()
    {
      oak::addEventListener<DamageTakenEvent, DamageTakenListener>(EVENT_ON_DAMAGE_TAKEN, this);
    }

    ~DamageTakenListener()
    {
      oak::removeEventListener<DamageTakenEvent, DamageTakenListener>(EVENT_ON_DAMAGE_TAKEN, listenerID);
    }


    uint getListenerID()
    {
      return listenerID;
    }

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