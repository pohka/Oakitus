#include "collision.h"

using namespace oak;

bool Collision::checkRectRect(const CollisionRect& a, const CollisionRect& b)
{
  return (
    std::abs(a.originX() - b.originX()) < (a.width() * 0.5f + b.width() * 0.5f) &&
    std::abs(a.originY() - b.originY()) < (a.height() * 0.5f + b.height() * 0.5f)
  );
}
bool Collision::checkRectCircle(const CollisionRect& a, const CollisionCircle& b)
{
  return false;
}

bool Collision::checkCircleCircle(const CollisionCircle& a, const CollisionCircle& b)
{
  float sqrdDist = std::powf(a.originX() - b.originX(), 2.0f) + std::powf(b.originY() - a.originY(), 2.0f);
  float sqrdMaxDist = std::powf(a.getRadius() + b.getRadius(), 2);

  return sqrdDist < sqrdMaxDist;
}