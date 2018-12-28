#ifndef ACTOR_H
#define ACTOR_H

#include "entity.h"

namespace oak
{
  struct Actor : public Entity
  {
    Actor();
    ~Actor();
  };
}

#endif