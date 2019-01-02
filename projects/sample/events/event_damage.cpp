#include "event_damage.h"

using namespace oak;
using namespace sample;

void sample::onDamageTaken(const DamageEventData& data)
{
  std::cout << "-- Event: onDamageTaken --" << std::endl
    << "damage:" << data.amount << std::endl
    << "attackerID:" << data.attackerID << std::endl
    << "victimID:" << data.victimID << std::endl;
}