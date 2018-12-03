#ifndef COLLISION_H
#define COLLISION_H

#include "collision_rect.h"
#include "collision_circle.h"
#include <glm/glm.hpp>

namespace oak
{
  

  ///<summary>Checking for collision</summary>
  class Collision
  {
    friend class Oakitus;

    public:
      ///<summary>Returns true if 2 rects overlap</summary>
      static bool checkRectRect(const CollisionRect& a, const CollisionRect& b);

      ///<summary>Returns true if a rect and circle overlap</summary>
      static bool checkRectCircle(const CollisionRect& a, const CollisionCircle& b);

      ///<summary>Returns true if 2 circles overlap</summary>
      static bool checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b);

      
      

  private:
    ///<summary>Resolve the current collisions</summary>
    static void resolveCollisions();

    //helper function to find the closest corner on a rect to a circle
    static glm::vec2 findRectClosestCornerToCircle(
      const CollisionRect& rect, 
      const CollisionCircle& circle
    );

    //check the collision between 2 Entitys
    static bool checkEntEntCollision(Entity* entA, Entity* entB);

    //helper function to check the side of a rect overlaps with a circle
    static bool sideCheckRectCircle(
      const CollisionRect& rect,
      const CollisionCircle& circle
    );
  };
}
#endif