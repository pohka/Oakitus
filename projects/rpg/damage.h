#ifndef DAMAGE_H
#define DAMAGE_H

#include "events/damage_data.h"
#include "unit.h"

namespace game
{
  struct Damage
  {
    //calcuate damage before vicitms reductions
    static void calcTotalAmount(game::DamageData& damage);

    //calcuate final damage that should be applied to the victim
    static int calcAfterReductions(Unit* victim, DamageData& damage);

    //apply damage to a unit with damage data
    static void apply(game::DamageData& rawDamage);

    static void apply(float amount, uchar element, uint casterID, uint victimID);
  };
}

#endif