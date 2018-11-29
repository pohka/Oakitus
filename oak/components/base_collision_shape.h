#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include "../core/component.h"

namespace oak
{
  class CollisionRect;
  class CollisionCircle;

  enum CollisionShape
  {
    RECT,
    CIRCLE
  };

  class BaseCollisionShape : public Component
  {

    public:
      virtual bool intersects(const CollisionRect& shape) const = 0;
      virtual bool intersects(const CollisionCircle& shape) const = 0;

      CollisionShape getType()
      {
        return type;
      }

      float originX() const
      {
        return this->entity->position.x + offsetX;
      }

      float originY() const
      {
        return this->entity->position.x + offsetX;
      }

    protected:
      CollisionShape type;
      float offsetX;
      float offsetY;
      uint VAO, VBO;
      uint textureID;

      
  };

}
#endif