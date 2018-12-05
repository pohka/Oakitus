#ifndef U_DUMMY_H
#define U_DUMMY_H

#include "../unit.h"
#include "../events/damage_listener.h"

namespace game
{
  namespace prefab
  {
    class UDummy : public Unit, public DamageListener
    {
      public:
        UDummy();
        ~UDummy();

        void onDamageTaken(int amount) override;
    };
  }
}

#endif