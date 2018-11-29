#ifndef COLLISION_CIRCLE_H
#define COLLISION_CIRCLE_H

#include "base_collision_shape.h"


namespace oak
{
  class CollisionCircle : public BaseCollisionShape
  {
    float radius;

  public:
    CollisionCircle(float radius, float offsetX, float offsetY);
    ~CollisionCircle();

    bool intersects(const CollisionRect& shape) const override;
    bool intersects(const CollisionCircle& shape) const override;
    float getRadius() const;

  };
}

#endif