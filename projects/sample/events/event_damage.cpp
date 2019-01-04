#include "event_damage.h"

#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <iostream>
#endif

using namespace oak;
using namespace sample;

void sample::onDamageTaken(const DamageEventData& data)
{
#ifdef DEBUG_MODE
  std::cout << "-- Event: onDamageTaken --" << std::endl
    << "damage:" << data.amount << std::endl
    << "attackerID:" << data.attackerID << std::endl
    << "victimID:" << data.victimID << std::endl;
#endif
}
