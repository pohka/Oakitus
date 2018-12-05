#ifndef DAMAGE_DATA_H
#define DAMAGE_DATA_H

#include <event/event_data.h>

namespace game
{
  struct DamageData : public oak::EventData
  {
    int amount;
  };
}

#endif