#include "collision.h"
#include <cmath>
#include <cstdlib>
#include "../debug.h"
#include "../core/entity.h"
#include "collision_layer.h"
#include "../oak_def.h"


using namespace oak;

bool Collision::checkRectRect(const CollisionRect& a, const CollisionRect& b)
{
  return (
    std::abs(a.originX() - b.originX()) < (a.width() * 0.5f + b.width() * 0.5f) &&
    std::abs(a.originY() - b.originY()) < (a.height() * 0.5f + b.height() * 0.5f)
  );
}
bool Collision::checkRectCircle(const CollisionRect& rect, const CollisionCircle& circle)
{
  //STEP 1: treat rectangle like a circle (quick check)
    //take the largest dimension on the rectangle and use that as the radius
  float maxDimension = rect.width();
  if (rect.width() < rect.height()) 
  {
    maxDimension = rect.height();
  }

  float originSqrdDist =
    std::pow((rect.originX() - circle.originX()), 2.0f) +
    std::pow((rect.originY() - circle.originY()), 2.0f);

  //if no within range of the quick check, return false
  if(!(originSqrdDist < std::pow(maxDimension + circle.getRadius(), 2.0f)) )
  {
    return false;
  }

  //----------


  //STEP 2: check if circle within rect
  float diffX = std::abs(rect.originX() - circle.originX());
  float diffY = std::abs(rect.originY() - circle.originY());

  if (diffX < rect.width() / 2.0f && diffY < rect.height() / 2.0f) {
    return true;
  }

  //----------

  //STEP 3: check closest corner
  glm::vec2 closestPoint = findRectClosestCornerToCircle(rect, circle);

  //compare squared distance with squared radius
  float squaredDistToClosestPoint =
    std::pow(closestPoint.x - circle.originX(), 2.0f) +
    std::pow(closestPoint.y - circle.originY(), 2.0f);

  if (squaredDistToClosestPoint < circle.getRadius() * circle.getRadius())
  {
    return true;
  }

  //STEP 4: collision with side of rectangle and circle, but not colliding with corners
  return sideCheckRectCircle(rect,  circle);
}

bool Collision::checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b)
{
  float sqrdDist = std::pow(a.originX() - b.originX(), 2.0f) + std::pow(b.originY() - a.originY(), 2.0f);
  float sqrdMaxDist = std::pow(a.getRadius() + b.getRadius(), 2);

  return sqrdDist < sqrdMaxDist;
}

 glm::vec2 Collision::findRectClosestCornerToCircle(const CollisionRect& rect, const CollisionCircle& circle) {
  //check closest corner
  //find corner of rect closest to circle
   float pointX = rect.minX();
   float pointY = rect.minY();

  //circle is left side
  if (circle.originX() < rect.originX())
  {
    //bottom left
    if (circle.originY() < rect.originY())
    {
      pointX = rect.minX();
      pointY = rect.minY();
    }
    //top left
    else 
    {
      pointX = rect.minX();
      pointY = rect.maxY();
    }
  }
  //circle is to right side
  else 
  {
    //bottom right
    if (circle.originY() < rect.originY())
    {
      pointX = rect.maxX();
      pointY = rect.minY();
    }
    //top right
    else 
    {
      pointX = rect.maxX();
      pointY = rect.maxY();
    }
  }

  return glm::vec2(pointX, pointY);
}

 //checks collision if side of rect intersects circle but with no corners
bool Collision::sideCheckRectCircle(
   const CollisionRect& rect,
   const CollisionCircle& circle)
 {
   //closest point on circumfrence of circle to the rectangle on a single axis

   //if X-axis has possible side collision
   if (circle.originY() < rect.maxY() && circle.originY() > rect.minY())
   {
     float circleEdgeX;

     //circle left of rect
     if (circle.originX() < rect.originX())
     {
       circleEdgeX = circle.originX() + circle.getRadius();
     }
     //circle right of rect
     else {
       circleEdgeX = circle.originX() - circle.getRadius();
     }

     float distOnX = std::abs(circleEdgeX - rect.originX());
     if (distOnX < rect.width() / 2.0f) {
       return true;
     }
   }

   //if Y-axis has possible side collision
   if (circle.originX() < rect.maxX() && circle.originX() > rect.minX()) {
     float circleEdgeY;

     //circle below rect
     if (circle.originY() < rect.originY()) {
       circleEdgeY = circle.originY() + circle.getRadius();
     }
     //circle above rect
     else {
       circleEdgeY = circle.originY() - circle.getRadius();
     }

     float distOnY = std::abs(circleEdgeY - rect.originY());
     if (distOnY < rect.height() / 2.0f) {
       return true;
     }
   }

   return false;
 }

//todo: is this even being used?
bool Collision::checkEntEntCollision(Entity* entA, Entity* entB)
{
  for (uint a = 0; a < entA->collisionShapes.size(); a++)
  {
    BaseCollisionShape* colA = entA->collisionShapes[a];
    for (uint b = 0; b < entB->collisionShapes.size(); b++)
    {
      BaseCollisionShape* colB = entB->collisionShapes[b];
      if (colA->intersects(*colB))
      {
        // LOG << "HAS COLLISION";
        entA->onCollisionHit(*entB);
        entB->onCollisionHit(*entA);
        return true;
      }
    }
  }
  return false;
}

void Collision::checkEntEntTrigger(Entity* entA, Entity* entB)
{
  for (uint a = 0; a < entA->collisionShapes.size(); a++)
  {
    BaseCollisionShape* colA = entA->collisionShapes[a];
    for (uint b = 0; b < entB->collisionShapes.size(); b++)
    {
      BaseCollisionShape* colB = entB->collisionShapes[b];
      //overlap fround
      if (colA->intersects(*colB))
      {
        entA->onCollisionHit(*entB);
        entB->onCollisionHit(*entA);
        return; //only trigger once
      }
    }
  }
}

//update rigidbodys to current entity position
//dynamic dynamic solve
//dynamic static solve
//set rigidbody last position to solved position
//set entity position to the solved postion
//check triggers
void Collision::resolveCollisions()
{
  if (Entity::entitys.size() <= 1)
  {
    return;
  }

  //pointers to increase readablity of loops
  Entity* ent;
  BaseRigidBody* rb;
  
  //set the rigidbody variables based on the current entity position
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
    ent = Entity::entitys[i];
    rb = ent->rigidBody;

    if (rb != nullptr && rb->isStatic == false)
    {
      rb->desiredNextPos = ent->position;
      rb->nextPos = rb->desiredNextPos;
      rb->velocity = rb->desiredNextPos - rb->lastPos;
    }
  }

  //resolve 
  for (uint a = 0; a < Entity::entitys.size() - 1; a++)
  {
    for (uint b = a + 1; b < Entity::entitys.size(); b++)
    {
      solve1(Entity::entitys[a], Entity::entitys[b]);
    }
  }

  //update the resolved positions
  for (uint i = 0; i < Entity::entitys.size(); i++)
  {
     ent = Entity::entitys[i];
     rb = ent->rigidBody;

    if (rb != nullptr && rb->isStatic == false)
    {
      rb->lastPos = Entity::entitys[i]->rigidBody->nextPos;
      ent->position = Entity::entitys[i]->rigidBody->nextPos;
    }
  }

  //check triggers
  for (uint a = 0; a < Entity::entitys.size() - 1; a++)
  {
    for (uint b = a + 1; b < Entity::entitys.size(); b++)
    {
      checkEntEntTrigger(Entity::entitys[a], Entity::entitys[b]);
    }
  }
}

void Collision::solve1(Entity* entA, Entity* entB)
{
  //static x dynamic
  if (entA->rigidBody != nullptr && entB->rigidBody != nullptr)
  {
    //static x dynamic
    if (entA->rigidBody->isStatic == true && entB->rigidBody->isStatic == false)
    {
      solveStaticDynamic(entA, entB);
    }
    //dynamic x static
    else if (entA->rigidBody->isStatic == false && entB->rigidBody->isStatic == true)
    {
      solveStaticDynamic(entB, entA);
    }

    //dynamic x dynamic
    else if (entA->rigidBody->isStatic == false && entB->rigidBody->isStatic == false)
    {
      solveDynamicDynamic(entA, entB);
    }
  }
}

glm::vec3 Collision::colliderDesiredPos(Entity* ent, BaseCollisionShape* shape)
{
  return ent->rigidBody->desiredNextPos + shape->offset();
}

void Collision::solveStaticDynamic(Entity* staticEnt, Entity* dynamicEnt)
{
  for (uint a = 0; a < staticEnt->collisionShapes.size(); a++)
  {
    BaseCollisionShape* staticCol = staticEnt->collisionShapes[a];

    if(staticCol->isTrigger == false)
    {
      for (uint b = 0; b < dynamicEnt->collisionShapes.size(); b++)
      {
        BaseCollisionShape* dynamicCol = dynamicEnt->collisionShapes[b];
        
        //both are physical and have collision
        if (dynamicCol->isTrigger == false && dynamicCol->intersects(*staticCol))
        {
          
          if (dynamicCol->getType() == COLLISION_SHAPE_RECT)
          {
            CollisionRect* dynamicRect = static_cast<CollisionRect*>(dynamicCol);

            //solve rect rect
            if (staticCol->getType() == COLLISION_SHAPE_RECT)
            {
              CollisionRect* staticRect = static_cast<CollisionRect*>(staticCol);

              solveStaticRectDynamicRect(
                staticEnt,
                staticRect,
                dynamicEnt,
                dynamicRect
              );
            }

            //solve rect circle
            else if (staticCol->getType() == COLLISION_SHAPE_CIRCLE)
            {
              CollisionCircle* staticCircle = static_cast<CollisionCircle*>(staticCol);

              solveStaticCircleDynamicRect(
                staticEnt,
                staticCircle,
                dynamicEnt,
                dynamicRect
              );
            }
          }
          else if (dynamicCol->getType() == COLLISION_SHAPE_CIRCLE)
          {
            CollisionCircle* dynamicCircle = static_cast<CollisionCircle*>(dynamicCol);

            //solve circle rect
            if (staticCol->getType() == COLLISION_SHAPE_RECT)
            {
              CollisionRect* staticRect = static_cast<CollisionRect*>(staticCol);
              
              solveStaticRectDynamicCircle(
                staticEnt,
                staticRect,
                dynamicEnt,
                dynamicCircle
              );
            }
            //solve circle rect
            else if (staticCol->getType() == COLLISION_SHAPE_CIRCLE)
            {
              CollisionCircle* staticCircle = static_cast<CollisionCircle*>(staticCol);
              solveStaticCricleDynamicCircle(
                staticEnt,
                staticCircle,
                dynamicEnt,
                dynamicCircle
              );
            }
          }
        }
      }
    }
  }
}

void Collision::solveStaticRectDynamicRect(
  Entity* staticEnt,
  CollisionRect* staticRect,
  Entity* dynamicEnt,
  CollisionRect* dynamicRect
)
{
  glm::vec3 dynamicRectOrigin = dynamicEnt->rigidBody->nextPos + dynamicRect->offset();


  //first check the direction the dynamic rect is in relation to the static rect
  bool isLeft = dynamicRectOrigin.x < staticRect->originX();
  bool isUp = dynamicRectOrigin.y > staticRect->originY();

  float diffX;
  float diffY;
  if (isLeft)
  {
    //difference on x-axis between the right side of dynamic rect and left side of static rect
    diffX = (dynamicRectOrigin.x + (dynamicRect->width() * 0.5f)) - (staticRect->originX() - (staticRect->width() *0.5f));
  }
  else
  {
    //difference on x-axis between the left side of dynamic rect and right side of static rect
    diffX = (dynamicRectOrigin.x - (dynamicRect->width() * 0.5f)) - (staticRect->originX() + (staticRect->width() *0.5f));
  }

  if (isUp)
  {
    //difference on y-axis between the bottom side of dynamic rect and top side of static rect
    diffY = (dynamicRectOrigin.y - (dynamicRect->height() * 0.5f)) - (staticRect->originY() + (staticRect->height() *0.5f));
  }
  else
  {
    //difference on y-axis between the top side of dynamic rect and bottom side of static rect
    diffY = (dynamicRectOrigin.y + (dynamicRect->height() * 0.5f)) - (staticRect->originY() - (staticRect->height() *0.5f));
  }

  //depth of collision on each axis
  float depthX = std::abs(diffX);
  float depthY = std::abs(diffY);

  //use the smallest depth for resolve
  if (depthX < depthY)
  {
    if (isLeft)
    {
      dynamicEnt->rigidBody->nextPos.x -= depthX;
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.x += depthX;
    }
  }
  else
  {
    if (isUp)
    {
      dynamicEnt->rigidBody->nextPos.y += depthY;
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.y -= depthY;
    }
  }
}

//2 cases
//corner case: 
// find depth of collision on single corner and solve by axis wtih the smallest depth
//side case:
// find side rect is on and solve by setting the rect colliding side to touch radius of the circle on that axis
void Collision::solveStaticCircleDynamicRect(
  Entity* staticEnt,
  CollisionCircle* staticCircle,
  Entity* dynamicEnt,
  CollisionRect* dynamicRect
)
{
  glm::vec3 dynamicRectOrigin = dynamicEnt->rigidBody->nextPos + dynamicRect->offset();

  //first check the direction the dynamic rect is in relation to the static rect
  bool isLastLeft = dynamicEnt->rigidBody->lastPos.x + dynamicRect->offsetX() < staticCircle->originX();
  bool isLastUp = dynamicEnt->rigidBody->lastPos.y + dynamicRect->offsetY() > staticCircle->originY();

  
  //half rect size
  float rectHalfW = dynamicRect->width() * 0.5f;
  float rectHalfH = dynamicRect->height() * 0.5f;

  bool isSideCaseX = (
    dynamicRectOrigin.x + rectHalfW > staticCircle->originX() &&
    dynamicRectOrigin.x - rectHalfW < staticCircle->originX()
  );

  bool isSideCaseY = (
    dynamicRectOrigin.y + rectHalfH > staticCircle->originY() &&
    dynamicRectOrigin.y - rectHalfH < staticCircle->originY()
  );

  //SIDE CASE: on top or bottom of circle
  if (isSideCaseX)
  {
    if (isLastUp)
    {
      dynamicEnt->rigidBody->nextPos.y = staticCircle->originY() + staticCircle->getRadius() + rectHalfH - dynamicRect->offsetY();
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.y = staticCircle->originY() - staticCircle->getRadius() - rectHalfH - dynamicRect->offsetY();
    }
  }
  //SIDE CASE: on left or right of circle
  else if (isSideCaseY)
  {
    if (isLastLeft)
    {
      dynamicEnt->rigidBody->nextPos.x = staticCircle->originX() - staticCircle->getRadius() - rectHalfW - dynamicRect->offsetX();
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.x = staticCircle->originX() + staticCircle->getRadius() + rectHalfW - dynamicRect->offsetX();
    }
  }
  //CORNER CASE
  else
  {
    //rect side for next pos
    bool isNextLeft = dynamicEnt->rigidBody->nextPos.x + dynamicRect->offsetX() < staticCircle->originX();
    bool isNextUp = dynamicEnt->rigidBody->nextPos.y + dynamicRect->offsetY() > staticCircle->originY();

    //difference bewteen rect side and origin of circle, for each axis
    float rectX, rectY;

    if (isNextLeft)
    {
      rectX = dynamicRectOrigin.x + rectHalfW - staticCircle->originX();
    }
    else
    {
      rectX = dynamicRectOrigin.x - rectHalfW - staticCircle->originX();
    }

    if (isNextUp)
    {
      rectY = dynamicRectOrigin.y - rectHalfH - staticCircle->originY();
    }
    else
    {
      rectY = dynamicRectOrigin.y + rectHalfH - staticCircle->originY();
    }

    rectX = std::abs(rectX);
    rectY = std::abs(rectY);

    //distance from circle origin to circle intersection, for each axis
    //using pythagoras therom
    float intersectDistX = ((rectY*rectY) - (staticCircle->getRadius() * staticCircle->getRadius()));
    float intersectDistY = ((rectX*rectX) - (staticCircle->getRadius() * staticCircle->getRadius()));


    intersectDistX = std::sqrtf(std::abs(intersectDistX));
    intersectDistY = std::sqrtf(std::abs(intersectDistY));

    //depth of collision for each axis
    float depthX = std::abs(intersectDistX - rectX);
    float depthY = std::abs(intersectDistY - rectY);
    
    //solve by the smallest depth
    if (depthX < depthY)
    {
      if (isNextLeft)
      {
        dynamicEnt->rigidBody->nextPos.x -= depthX;
      }
      else
      {
        dynamicEnt->rigidBody->nextPos.x += depthX;
      }
    }
    else
    {
      if (isNextUp)
      {
        dynamicEnt->rigidBody->nextPos.y += depthY;
      }
      else
      {
        dynamicEnt->rigidBody->nextPos.y -= depthY;
      }
    }
  }
}

void Collision::solveStaticCricleDynamicCircle(
  Entity* staticEnt,
  CollisionCircle* staticCircle,
  Entity* dynamicEnt,
  CollisionCircle* dynamicCircle
)
{
  glm::vec3 direction = glm::normalize((dynamicEnt->rigidBody->nextPos + dynamicCircle->offset()) - glm::vec3(staticCircle->originX(), staticCircle->originY(), 0.0f));
  float minDist = staticCircle->getRadius() + dynamicCircle->getRadius();
  dynamicEnt->rigidBody->nextPos = staticEnt->position + staticCircle->offset() - dynamicCircle->offset() + (direction * minDist);
}

void Collision::solveStaticRectDynamicCircle(
  Entity* staticEnt,
  CollisionRect* staticRect,
  Entity* dynamicEnt,
  CollisionCircle* dynamicCircle
)
{
  glm::vec3 dynamicCircleOrigin = dynamicEnt->rigidBody->nextPos + dynamicCircle->offset();

  //first check the direction the dynamic circle is in relation to the static rect
  bool isLastLeft = dynamicEnt->rigidBody->lastPos.x + dynamicCircle->offsetX() < staticRect->originX();
  bool isLastUp = dynamicEnt->rigidBody->lastPos.y + dynamicCircle->offsetY() > staticRect->originY();


  //half rect size
  float rectHalfW = staticRect->width() * 0.5f;
  float rectHalfH = staticRect->height() * 0.5f;

  bool isSideCaseX = (
    dynamicCircleOrigin.x < staticRect->originX() + rectHalfW &&
    dynamicCircleOrigin.x > staticRect->originX() - rectHalfW
  );

  bool isSideCaseY = (
    dynamicCircleOrigin.y < staticRect->originY() + rectHalfH &&
    dynamicCircleOrigin.y > staticRect->originY() - rectHalfH
  );

  //SIDE CASE: circle on top or bottom side of rect
  if (isSideCaseX)
  {
    if (isLastUp)
    {
      dynamicEnt->rigidBody->nextPos.y = staticRect->originY() + rectHalfH + dynamicCircle->getRadius() - dynamicCircle->offsetY();
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.y = staticRect->originY() - rectHalfH - dynamicCircle->getRadius() - dynamicCircle->offsetY();
    }
  }
  //SIDE CASE: circle on left or right side of rect
  else if (isSideCaseY)
  {
    if (isLastLeft)
    {
      dynamicEnt->rigidBody->nextPos.x = staticRect->originX() - rectHalfW - dynamicCircle->getRadius() - dynamicCircle->offsetX();
    }
    else
    {
      dynamicEnt->rigidBody->nextPos.x = staticRect->originX() + rectHalfW + dynamicCircle->getRadius() - dynamicCircle->offsetX();
    }
  }

  //CORNER CASE
  else
  {
    //circle side for next position
    bool isNextLeft = dynamicEnt->rigidBody->nextPos.x + dynamicCircle->offsetX() < staticRect->originX();
    bool isNextUp = dynamicEnt->rigidBody->nextPos.y + dynamicCircle->offsetY() > staticRect->originY();

    //difference bewteen rect side and origin of circle, for each axis
    float rectX, rectY;
    
    if (isNextLeft)
    {
      rectX = staticRect->originX() - rectHalfW - dynamicCircleOrigin.x;
    }
    else
    {
      rectX = staticRect->originX() + rectHalfW - dynamicCircleOrigin.x;
    }

    if (isNextUp)
    {
      rectY = staticRect->originY() + rectHalfH - dynamicCircleOrigin.y;
    }
    else
    {
      rectY = staticRect->originY() - rectHalfH - dynamicCircleOrigin.y;
    }

    rectX = std::abs(rectX);
    rectY = std::abs(rectY);

    //distance from circle origin to circle intersection, for each axis
    //using pythagoras therom
    float intersectDistX = ((rectY*rectY) - (dynamicCircle->getRadius() * dynamicCircle->getRadius()));
    float intersectDistY = ((rectX*rectX) - (dynamicCircle->getRadius() * dynamicCircle->getRadius()));


    intersectDistX = std::sqrtf(std::abs(intersectDistX));
    intersectDistY = std::sqrtf(std::abs(intersectDistY));

    //depth of collision for each axis
    float depthX = std::abs(intersectDistX - rectX);
    float depthY = std::abs(intersectDistY - rectY);

    //solve by the smallest depth
    if (depthX < depthY)
    {
      if (isNextLeft)
      {
        dynamicEnt->rigidBody->nextPos.x -= depthX;
      }
      else
      {
        dynamicEnt->rigidBody->nextPos.x += depthX;
      }
    }
    else
    {
      if (isNextUp)
      {
        dynamicEnt->rigidBody->nextPos.y += depthY;
      }
      else
      {
        dynamicEnt->rigidBody->nextPos.y -= depthY;
      }
    }
  }
}

void Collision::solveDynamicDynamic(Entity* entA, Entity* entB)
{
  for (uint a = 0; a < entA->collisionShapes.size(); a++)
  {
    BaseCollisionShape* colA = entA->collisionShapes[a];

    if (colA->isTrigger == false)
    {
      for (uint b = 0; b < entB->collisionShapes.size(); b++)
      {
        BaseCollisionShape* colB = entB->collisionShapes[b];

        //both are physical and have collision
        if (colB->isTrigger == false && colA->intersects(*colB))
        {
          
          if (colA->getType() == COLLISION_SHAPE_RECT)
          {
            CollisionRect* rectA = static_cast<CollisionRect*>(colA);

            if (colB->getType() == COLLISION_SHAPE_RECT)
            {
              CollisionRect* rectB = static_cast<CollisionRect*>(colB);
            }
            else if (colB->getType() == COLLISION_SHAPE_CIRCLE)
            {
              CollisionCircle* circleB = static_cast<CollisionCircle*>(colB);
            }
          }

          if (colA->getType() == COLLISION_SHAPE_CIRCLE)
          {
            CollisionCircle* circleA = static_cast<CollisionCircle*>(colA);

            if (colB->getType() == COLLISION_SHAPE_RECT)
            {
              CollisionRect* rectB = static_cast<CollisionRect*>(colB);
            }
            else if (colB->getType() == COLLISION_SHAPE_CIRCLE)
            {
              CollisionCircle* circleB = static_cast<CollisionCircle*>(colB);
              solveDynamicCircleDynamicCircle(
                entA,
                circleA,
                entB,
                circleB
              );
            }
          }
        }
      }
    }
  }
}

void Collision::solveDynamicCircleDynamicCircle(
  Entity* entA,
  CollisionCircle* circleA,
  Entity* entB,
  CollisionCircle* circleB
)
{
  //velocity of each rigidbody
  glm::vec3 velA = entA->rigidBody->velocity;
  glm::vec3 velB = entB->rigidBody->velocity;

  float massA = entA->rigidBody->mass;
  float massB = entB->rigidBody->mass;

  //difference of next position direction
  glm::vec3 diffDir = glm::normalize(entB->rigidBody->nextPos - entA->rigidBody->nextPos);

  //resulting change vector of impact, in relation to entA
  glm::vec3 resultForce = glm::vec3(
    (velA.x + velB.x) * 0.5f,
    (velA.y + velB.y) * 0.5f,
    0.0f
  );

  //min seperation dist
  float minDiff = circleA->getRadius() + circleB->getRadius();

  //which ever entity has the highest mass use that for setting the result force
  if (massA > massB)
  {
    entA->rigidBody->nextPos = entA->rigidBody->lastPos + resultForce;

    //find direction vector between 2 next positions
    glm::vec3 diff = (entB->rigidBody->lastPos + circleB->offset()) - (entA->rigidBody->nextPos + circleA->offset());
    glm::vec3 dir = glm::normalize(diff);

    //set next position and update velocity
    entA->rigidBody->velocity = entA->rigidBody->nextPos - entA->rigidBody->lastPos;
    entB->rigidBody->nextPos = entA->rigidBody->nextPos + (dir * minDiff * 1.0f);
    entB->rigidBody->velocity = entB->rigidBody->nextPos - entB->rigidBody->lastPos;
  }
  else
  {
    entB->rigidBody->nextPos = entB->rigidBody->lastPos + resultForce;

    //find direction vector between 2 next positions
    glm::vec3 diff = (entA->rigidBody->lastPos + circleA->offset()) - (entB->rigidBody->nextPos + circleB->offset());
    glm::vec3 dir = glm::normalize(diff);

    //set next position and update velocity
    entB->rigidBody->velocity = entB->rigidBody->nextPos - entB->rigidBody->lastPos;
    entA->rigidBody->nextPos = entB->rigidBody->nextPos + (dir * minDiff * 1.0f);
    entA->rigidBody->velocity = entA->rigidBody->nextPos - entA->rigidBody->lastPos;
  }
}