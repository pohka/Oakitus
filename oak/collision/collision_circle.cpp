#include "collision.h"
#include <core/resources.h>
#include <oak_def.h>

using namespace oak;

CollisionCircle::CollisionCircle(float radius, float offsetX, float offsetY)
{
  this->radius = radius;
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  type = COLLISION_SHAPE_CIRCLE;

  textureID = Resources::getTextureIDBySrc("circle.png");

  float d = radius * 2.0f;
  initVAO(d, d);
}

CollisionCircle::~CollisionCircle()
{

}

bool CollisionCircle::intersectsRect(const CollisionRect& shape) const
{
  return Collision::checkRectCircle(shape, *this);
}
bool CollisionCircle::intersectsCircle(const CollisionCircle& shape) const
{
  return Collision::checkCircleCircle(*this, shape);
}

float CollisionCircle::getRadius() const
{
  return radius;
}