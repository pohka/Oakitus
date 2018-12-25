#ifndef E_DAMAGE_TAKEN_H
#define E_DAMAGE_TAKEN_H

#include <oak/event/event.h>
#include "../game_def.h"
#include "damage_data.h"

namespace game
{
  //typedef
  class DamageTakenListener;
  struct DamageData;
  typedef oak::Event<DamageTakenListener, DamageData> DamageTakenEvent;
  typedef oak::BaseListener<DamageTakenEvent, DamageTakenListener> BaseDamageTakenListener;

  class DamageTakenListener : public BaseDamageTakenListener
  {
  public:
    DamageTakenListener(const uchar eventID = EVENT_ON_DAMAGE_TAKEN) :
      BaseDamageTakenListener(eventID)
    {}
    ~DamageTakenListener() {}
    virtual void onDamageTaken(DamageData& data) = 0;
  };


  //onFire callback function
  template <typename Listener, typename Data>
  void  onDamageTakenFire(Listener* listener, Data& data)
  {
    listener->onDamageTaken(data);
  }
}

#endif