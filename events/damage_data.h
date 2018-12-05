#ifndef DAMAGE_DATA_H
#define DAMAGE_DATA_H

#include <event/event_data.h>

namespace game
{
  class DamageData : public oak::EventData
  {
  public:
    DamageData()
    {

    }
    int amount;
  };
}

#endif