#ifndef ACTOR_H
#define ACTOR_H

#include <oak/ecs/entity.h>
#include <oak/player/player_resource.h>

namespace oak
{
  class Player;

  class Actor : public Entity
  {
    Player* owner;

    public:
      friend class Player;
      Actor();
      Player* getOwner();
  };
}

#endif