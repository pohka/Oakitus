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
    //  ~Ability();
      Unit* caster;
      virtual void cast() = 0;
  };
}
#endif