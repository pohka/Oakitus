#ifndef PLAYER_H
#define PLAYER_H

#include <core/base_player.h>
#include "unit.h"

namespace game
{
  class Unit;

  class Player : public oak::BasePlayer
  {
    Unit* assignedUnit;
    

    public:
      Player();
      ~Player();

      void setAssignedUnit(Unit& unit);
      Unit* getAssignedUnit() const;
  };
}

#endif