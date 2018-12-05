#ifndef DAMAGE_LISTENER_H
#define DAMAGE_LISTENER_H

#include "damage_data.h"

namespace game
{
  struct DamageData;

  class DamageListener
  {
    public :
      virtual void onDamageTaken(DamageData& data) = 0;
  };
}

#endif