#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include "../core/component.h"

namespace oak
{
  class CollisionRect;
  class CollisionCircle;

  class BaseCollisionShape : public Component
  {

    public:
      BaseCollisionShape();
      ~BaseCollisionShape();
      virtual bool intersects(const CollisionRect& shape) const = 0;
      virtual bool intersects(const CollisionCircle& shape) const = 0;

      float originX() const;
      float originY() const;

      void onDebugDraw() const override;

    protected:
      float offsetX;
      float offsetY;
      uint VAO, VBO;
      uint textureID;

      void initVAO(float quadW, float quadH);
  };

}
#endif