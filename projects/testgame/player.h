#ifndef PLAYER_H
#define PLAYER_H

#include "oak/core/entity.h"

namespace game
{
  class Player : public oak::Entity
  {

    public:
      Player();
      ~Player();
  };
}

#endif