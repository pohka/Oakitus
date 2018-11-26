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
    Unit* unit;

    public :
      Player();
      ~Player();

      unsigned int getID();
  };
}

#endif