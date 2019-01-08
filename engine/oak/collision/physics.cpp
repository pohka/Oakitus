#include "physics.h"
#include <oak/ecs/entity_manager.h>
#include "base_collision_shape.h"
#include "collision_rect.h"

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
};

enum IntersectResult { PARALLEL, COINCIDENT, NOT_INTERESECTING, INTERESECTING };

int checkLine(const LineSegment& line, const LineSegment& other, glm::vec3& intersection)
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
    intersection.z = 0.0f;

    return INTERESECTING;
  }

  return NOT_INTERESECTING;
}


void checkRect(CollisionRect* rect, const LineSegment& other)
{
  LineSegment top = LineSegment(rect->minX(), rect->maxY(), rect->maxX(), rect->maxY());
  LineSegment bottom = LineSegment(rect->minX(), rect->minY(), rect->maxX(), rect->minY());
  LineSegment left = LineSegment(rect->minX(), rect->minY(), rect->minX(), rect->maxY());
  LineSegment right = LineSegment(rect->maxX(), rect->minY(), rect->maxX(), rect->maxY());

  glm::vec3 point;
  checkLine(top, other, point);
  //checkLine(bottom, other);
  //checkLine(left, other);
  //checkLine(right, other);
}

RaycastHit Physics::Raycast2D(const glm::vec3& origin, glm::vec3 direction, float distance, uint layers)
{
  direction.z = 0.0f;
  direction = glm::normalize(direction);
  glm::vec3 end = origin + (direction * distance);

  LineSegment line = LineSegment(origin.x, origin.y, end.x, end.y);

  std::vector<Entity*> entitys = EntityManager::getAllEntitys();
  for (Entity* ent : entitys)
  {
    glm::vec3 entPos = ent->transform->position();
    std::vector<BaseCollisionShape*> shapes = ent->getCollisionShapes();

    for (BaseCollisionShape* shape : shapes)
    {
      glm::vec3 colPos = entPos + shape->offset();

      switch (shape->getType())
      {
        case COLLISION_SHAPE_RECT:
          checkRect(static_cast<CollisionRect*>(shape), line);
          break;
        case COLLISION_SHAPE_CIRCLE:
          ; 
          break;
      }
    }
  }
}


