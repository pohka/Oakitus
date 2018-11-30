#ifndef COLLISION_H
#define COLLISION_H

#include "collision_rect.h"
#include "collision_circle.h"
#include <glm/glm.hpp>

namespace oak
{

  class Collision
  {
    public:
      static bool checkRectRect(const CollisionRect& a, const CollisionRect& b);
      static bool checkRectCircle(const CollisionRect& a, const CollisionCircle& b);
      static bool checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b);

  private:
    static glm::vec2 findRectClosestCornerToCircle(
      const CollisionRect& rect, 
      const CollisionCircle& circle
    );

    static bool sideCheckRectCircle(
      const CollisionRect& rect,
      const CollisionCircle& circle
    );
  };
}
#endif