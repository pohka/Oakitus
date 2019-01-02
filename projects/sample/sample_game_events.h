#ifndef SAMPLE_GAME_EVENTS_H
#define SAMPLE_GAME_EVENTS_H

#include <oak/event/alt_event.h>
#include <iostream>

namespace oak
{
  struct DamageEventData : public AltEventData
  {
    DamageEventData(int amount)
    {
      this->amount = amount;
    }
    int amount;
  };

  static void onDamage(const DamageEventData& data)
  {
    std::cout << "damage:" << data.amount << std::endl;
  }

  static void addGameEvents()
  {
    AltEventManager::addEvent(0, onDamage);
  }
}

#endif