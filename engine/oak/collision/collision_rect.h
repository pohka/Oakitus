#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H


#include "base_collision_shape.h"


namespace oak
{
  struct RectBounds
  {
    float minX;
    float minY;
    float maxX;
    float maxY;
  };

  class CollisionRect : public BaseCollisionShape
  {
    float w;
    float h;
    public:
      CollisionRect(float offsetX, float offsetY, float width, float height);
    
      bool intersectsRect(const CollisionRect& shape) const override;
      bool intersectsCircle(const CollisionCircle& shape) const override;

      float minX() const;
      float minY() const;
      float maxX() const;
      float maxY() const;
      float width() const;
      float height() const;

      RectBounds getRectBounds() const;

  };
}
#endif