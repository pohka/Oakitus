#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "collision_rect.h"
#include "collision_circle.h"
#include <glm/glm.hpp>

namespace oak
{
  

  //Checking for collision
  class Collision
  {
    friend class Oakitus;

    public:
      //Returns true if 2 rects overlap
      static bool checkRectRect(const CollisionRect& a, const CollisionRect& b);

      //Returns true if a rect and circle overlap
      static bool checkRectCircle(const CollisionRect& a, const CollisionCircle& b);

      //Returns true if 2 circles overlap
      static bool checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b);

      
      

  private:
    //Resolve the current collisions
    static void resolveCollisions();

    //helper function to find the closest corner on a rect to a circle
    static glm::vec2 findRectClosestCornerToCircle(
      const CollisionRect& rect, 
      const CollisionCircle& circle
    );

    //check the collision between 2 Entitys
    static bool checkEntEntCollision(Entity* entA, Entity* entB);

    static void solve1(Entity* entA, Entity* entB);
    static void solveStaticDynamic(Entity* staticEnt, Entity* dynamicEnt);
    static void solveDynamicDynamic(Entity* entA, Entity* entB);

    static void solveStaticRectDynamicRect(
      Entity* staticEnt, 
      CollisionRect* staticRect,
      Entity* dynamicEnt,
      CollisionRect* dynamicRect
    );

    static void solveStaticCircleDynamicRect(
      Entity* staticEnt,
      CollisionCircle* staticCircle,
      Entity* dynamicEnt,
      CollisionRect* dynamicRect
    );

    static void solveStaticCricleDynamicCircle(
      Entity* staticEnt,
      CollisionCircle* staticCircle,
      Entity* dynamicEnt,
      CollisionCircle* dynamicCircle
    );

    static void solveStaticRectDynamicCircle(
      Entity* staticEnt,
      CollisionRect* staticRect,
      Entity* dynamicEnt,
      CollisionCircle* dynamicCircle
    );

    static void solveDynamicCircleDynamicCircle(
      Entity* entA,
      CollisionCircle* circleA,
      Entity* entB,
      CollisionCircle* circleB
    );

    static glm::vec3 colliderDesiredPos(Entity* ent, CollisionShape* shape);

    //helper function to check the side of a rect overlaps with a circle
    static bool sideCheckRectCircle(
      const CollisionRect& rect,
      const CollisionCircle& circle
    );

    static void checkEntEntTrigger(Entity* entA, Entity* entB);
  };
}
#endif