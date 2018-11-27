#ifndef ABILITY_SHOOT_H
#define ABILITY_SHOOT_H

#include "../ability.h"

namespace game
{
  namespace ability
  {
    class Shoot : public Ability
    {
      public:
        Shoot();
        ~Shoot();

        void cast() override;
    };
  }
}

#endif