#ifndef DAMAGE_LISTENER_H
#define DAMAGE_LISTENER_H

#include <event/event_listener.h>

namespace game
{
  class DamageListener
  {
    virtual void onDamageTaken(int amount) = 0;

  public:
    void onFire(int amount)
    {
      onDamageTaken(amount);
    }

 // public :
    //DamageListener()
    //{
    //  onFire = this->onDamageTaken;
    //}
    
  };
}

#endif