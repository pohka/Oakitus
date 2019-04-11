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

    bool intersectsRect(const CollisionRect& shape) const override;
    bool intersectsCircle(const CollisionCircle& shape) const override;
    float getRadius() const;
    void setRadius(float radius);

  };
}

#endif