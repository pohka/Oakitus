#ifndef SAMPLE_DAMAGE_EVENT_H
#define SAMPLE_DAMAGE_EVENT_H

#include <oak/oak.h>
#include <iostream>

namespace sample
{
  //event data
  struct DamageEventData : public oak::IEventData
  {
    DamageEventData(
      const int amount,
      const uint attackerID,
      const uint victimID
    ) :
      amount(amount),
      attackerID(attackerID),
      victimID(victimID)
    {}

    const int amount;
    const uint attackerID;
    const uint victimID;
  };

  //callback function
  void onDamageTaken(const DamageEventData& data);
}

#endif