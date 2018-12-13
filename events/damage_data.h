#ifndef DAMAGE_DATA_H
#define DAMAGE_DATA_H

#include <event/event.h>

namespace game
{
  //event data
  struct DamageData : public oak::IEventData
  {
    int amount;
    uint victimID;
    uint attackerID;
  };
}

#endif