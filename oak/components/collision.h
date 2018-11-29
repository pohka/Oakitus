#ifndef COLLISION_H
#define COLLISION_H

#include "collision_rect.h"
#include "collision_circle.h"

namespace oak
{
  class Collision
  {
    public:
      static bool checkRectRect(const CollisionRect& a, const CollisionRect& b);
      static bool checkRectCircle(const CollisionRect& a, const CollisionCircle& b);
      static bool checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b);
  };
}
#endif