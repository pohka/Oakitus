#ifndef ABILITY_H
#define ABILITY_H

#include "unit.h"

namespace game
{
  class Unit;

  class Ability
  {
    

    public:
    //  Ability();
      virtual ~Ability() = default;
      Unit* caster;
      virtual void cast() = 0;
  };
}
#endif