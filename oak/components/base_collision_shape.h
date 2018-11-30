#ifndef BASE_COLLISION_SHAPE_H
#define BASE_COLLISION_SHAPE_H

#include <core/types.h>

namespace oak
{
  class CollisionRect;
  class CollisionCircle;
  class Entity;

  enum ShapeType
  {
    RECT,
    CIRCLE
  };

  class BaseCollisionShape
  {

    public:
      friend class Entity;

      BaseCollisionShape();
      ~BaseCollisionShape();
      bool intersects(BaseCollisionShape& shape);

      virtual bool intersectsRect(const CollisionRect& shape) const = 0;
      virtual bool intersectsCircle(const CollisionCircle& shape) const = 0;

      float originX() const;
      float originY() const;
      ShapeType getType() const;

      void onDebugDraw() const;
      

    protected:
      ShapeType type;
      float offsetX;
      float offsetY;
      uint VAO, VBO;
      uint textureID;
      Entity* entity;

      void initVAO(float quadW, float quadH);
  };

}
#endif