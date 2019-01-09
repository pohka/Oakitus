#include "physics.h"
#include <oak/ecs/entity_manager.h>
#include "base_collision_shape.h"
#include "collision_rect.h"
#include <iostream>
#include <bitset>

using namespace oak;


struct LineSegment
{
  const float x1, y1, x2, y2;

  LineSegment(const float x1, const float y1, const float x2, const float y2) :
    x1(x1),
    y1(y1),
    x2(x2),
    y2(y2)
  {
  }

  glm::vec2 getNormal()
  {
    float x = x2 - x1;
    float y = y2 - y1;
    return glm::vec2(y, -x);
  }
};

enum IntersectResult { PARALLEL, COINCIDENT, NOT_INTERESECTING, INTERESECTING };

int checkLine(const LineSegment& line, const LineSegment& other, glm::vec2& intersection)
{
  float denom = (
    (other.y2 - other.y1)*(line.x2 - line.x1)) -
    ((other.x2 - other.x1)*(line.y2 - line.y1)
      );

  float nume_a = (
    (other.x2 - other.x1)*(line.y1 - other.y1)) -
    ((other.y2 - other.y1)*(line.x1 - other.x1)
      );

  float nume_b = (
    (line.x2 - line.x1)*(line.y1 - other.y1)) -
    ((line.y2 - line.y1)*(line.x1 - other.x1)
  );

  if (denom == 0.0f)
  {
    if (nume_a == 0.0f && nume_b == 0.0f)
    {
      return COINCIDENT;
    }
    return PARALLEL;
  }

  float ua = nume_a / denom;
  float ub = nume_b / denom;

  if (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
  {
    // Get the intersection point.
    intersection.x = line.x1 + ua * (line.x2 - line.x1);
    intersection.y = line.y1 + ua * (line.y2 - line.y1);

    return INTERESECTING;
  }

  return NOT_INTERESECTING;
}

//returns true if hit, output is set in hit
bool checkRect(CollisionRect* rect, const LineSegment& other, RaycastHit2D& hit)
{
  RectBounds bounds = rect->getRectBounds();
  //nodes connected clockwise
  LineSegment top = LineSegment(bounds.minX, bounds.maxY, bounds.maxX, bounds.maxY); //top left -> top right
  LineSegment right = LineSegment(bounds.maxX, bounds.maxY, bounds.maxX, bounds.minY); //top right -> bottom right
  LineSegment bottom = LineSegment(bounds.maxX, bounds.minY, bounds.minX, bounds.minY); //bottom right -> bottom left
  LineSegment left = LineSegment(bounds.minX, bounds.minY, bounds.minX, bounds.maxY); //bottom left -> top left

  auto edges = { top, left, bottom, right };

  glm::vec2 point;
  glm::vec2 resultPt;
  LineSegment* edgeHit = nullptr;
  float closestDist = 0.0f;
  bool found = false;
  for (auto edge : edges)
  {
    //if intersecting the edge of rect
    if (checkLine(edge, other, point) == INTERESECTING)
    {
      //first intersection found
      if (!found)
      {
        resultPt = point;
        closestDist = glm::distance(glm::vec2(other.x1, other.y1), glm::vec2(point.x, point.y));
        found = true;
        edgeHit = &edge;
      }
      else
      {
        //uses closest intersection point
        float dist = glm::distance(glm::vec2(other.x1, other.y1), glm::vec2(point.x, point.y));
        if (dist < closestDist)
        {
          closestDist = dist;
          resultPt = point;
          edgeHit = &edge;
        }
      }
    }
  }


  if (found && edgeHit != nullptr)
  {
    hit.distance = closestDist;
    hit.point = resultPt;
    hit.normal = glm::normalize(edgeHit->getNormal());
  }

  return found;
}

bool Physics::Raycast2D(const glm::vec2& origin, glm::vec2 direction, RaycastHit2D& hit, float distance, uint layers)
{
  direction = glm::normalize(direction);
  glm::vec2 end = origin + (direction * distance);

  LineSegment line = LineSegment(origin.x, origin.y, end.x, end.y);
  bool found = false;
  RaycastHit2D outHit; //output of a intersection hit

  std::vector<Entity*> entitys = EntityManager::getAllEntitys();
  for (Entity* ent : entitys)
  {
    //bitwise check, if entity collision layer is in layers
    if ((ent->getCollisionLayer() & layers) > 0)
    {
      std::vector<BaseCollisionShape*> shapes = ent->getCollisionShapes();

      for (BaseCollisionShape* shape : shapes)
      {
        switch (shape->getType())
        {
          //rect
        case COLLISION_SHAPE_RECT:
          if (checkRect(static_cast<CollisionRect*>(shape), line, outHit))
          {
            //first intersection
            if (!found)
            {
              hit = outHit;
              hit.entityHit = ent;
              found = true;
            }
            //use closest intersection
            else if (hit.distance > outHit.distance)
            {
              hit = outHit;
              hit.entityHit = ent;
            }
          }
          break;
          //circle
        case COLLISION_SHAPE_CIRCLE:
          ; //todo
          break;
        }
      }
    }
  }

  return found;
}


