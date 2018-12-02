#ifndef SWORD_ATTACK_H
#define SWORD_ATTACK_H

#include "../ability.h"

namespace game
{
  class SwordAttack : public Ability
  {
    public:
      SwordAttack();
      ~SwordAttack();


      void onCast() override;
      void onAbilityStart() override;
      void onAbilityEnd() override;
  };
}


#endif