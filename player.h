#ifndef PLAYER_H
#define PLAYER_H

#include <core/base_player.h>
#include "unit.h"

namespace game
{
  class Unit;

  class Player : public oak::BasePlayer
  {
    uint assignedUnitID;
    bool hasAssignedUnit = false;
    

    public:
      Player();
      ~Player();

      void setAssignedUnit(Unit& unit);
      Unit* getAssignedUnit() const;
  };
}

#endif