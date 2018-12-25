#ifndef ABIL_SHOOT_H
#define ABIL_SHOOT_H

#include "../ability.h"

namespace game
{
  class abil_Shoot : public Ability
  {
    public:
      abil_Shoot();
      ~abil_Shoot();

      void onCast() override;
      void onAbilityStart() override;
      void onAbilityEnd() override;
  };
}

#endif