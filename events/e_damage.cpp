#include "e_damage.h"

using namespace game;

void EDamage::fire(int amount)
{
  for (uint i = 0; i < listeners.size(); i++)
  {
    DamageListener* lis = static_cast<DamageListener*>(listeners[i]);
    lis->onFire(amount);
  }
}