#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include "../core/component.h"

namespace oak
{
  enum CollisionType
  {
    BOX,
    CIRCLE
  };

  class CollisionShape : public Component
  {
    public:
      virtual bool intersects(CollisionShape& shape) const = 0;
      CollisionType getType()
      {
        return type;
      }
     // virtual void onDraw() const = 0;

    protected:
      CollisionType type;
  };

}
#endif