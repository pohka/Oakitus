#include "e_damage.h"
#include "../game_def.h"
#include "damage_data.h"

using namespace game;

EDamage::EDamage(uchar eventID) : Event(eventID)
{

}

void EDamage::fire(oak::EventData& data)
{
  DamageData& damData = static_cast<DamageData&>(data);

  for (uint i = 0; i < listeners.size(); i++)
  {
    listeners[i]->onDamageTaken(damData);
  }
}

void EDamage::addListener(DamageListener* listener)
{
  listeners.push_back(listener);
}