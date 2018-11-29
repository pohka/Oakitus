#include "collision.h"

using namespace oak;

CollisionCircle::CollisionCircle(float radius, float offsetX, float offsetY)
{
  this->radius = radius;
  this->offsetX = offsetX;
  this->offsetY = offsetY;
}

CollisionCircle::~CollisionCircle()
{

}

bool CollisionCircle::intersects(const CollisionRect& shape) const
{
  return Collision::checkRectCircle(shape, *this);
}
bool CollisionCircle::intersects(const CollisionCircle& shape) const
{
  return Collision::checkCircleCircle(*this, shape);
}

float CollisionCircle::getRadius() const
{
  return radius;
}