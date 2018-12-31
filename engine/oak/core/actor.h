#ifndef ACTOR_H
#define ACTOR_H

#include "entity.h"
#include "player.h"

namespace oak
{
  class Player;

  class Actor : public Entity
  {
    Player* owner;

    public:
      friend class Player;
      Actor();
      ~Actor();
      Player* getOwner();
  };
}

#endif