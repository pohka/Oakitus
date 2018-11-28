#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H


#include "collision_shape.h"

namespace oak
{

  class CollisionBox : public CollisionShape
  {
    float offsetX;
    float offsetY;
    float w;
    float h;

  public:
    CollisionBox(float offsetX, float offsetY, float width, float height);
    
    bool intersects(CollisionShape& shape) const;

    float minX() const;
    float minY() const;
    float maxX() const;
    float maxY() const;
    float width() const;
    float height() const;
    float originX() const;
    float originY() const;

    void onDebugDraw() const override;
  };
}
#endif