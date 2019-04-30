#pragma once
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H


#include "collision_shape.h"


namespace oak
{
  struct RectBounds
  {
    float minX;
    float minY;
    float maxX;
    float maxY;
  };

  class CollisionRect : public CollisionShape
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

      void setWidth(float w);
      void setHeight(float h);
      

      RectBounds getRectBounds() const;

  };
}
#endif