#ifndef ABIL_SWORD_ATTACK_H
#define ABIL_SWORD_ATTACK_H

#include "../ability.h"

namespace game
{
  class abil_SwordAttack : public Ability
  {
    public:
      abil_SwordAttack();
      ~abil_SwordAttack();


      void onCast() override;
      void onAbilityStart() override;
      void onAbilityEnd() override;
  };
}


#endif