#ifndef PLAYER_H
#define PLAYER_H

#include <core/id_generator.h>
#include <core/types.h>
#include "unit.h"

namespace game
{
  class Unit;

  class Player
  {
    static oak::IDGenerator idGen;
    uint playerID;
    Unit* assignedUnit;
    

    public :
      

      Player();
      ~Player();

      uint getID();
      void setAssignedUnit(Unit& unit);
      Unit& getAssignedUnit();
  };
}

#endif