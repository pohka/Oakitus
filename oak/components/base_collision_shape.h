#ifndef BASE_COLLISION_SHAPE_H
#define BASE_COLLISION_SHAPE_H

#include <core/types.h>

///<summary>The base collision shape</summary>
namespace oak
{
  class CollisionRect;
  class CollisionCircle;
  class Entity;

  //all type of collision shapes
  cnum COLLISION_SHAPE_RECT = 0;
  cnum COLLISION_SHAPE_CIRCLE = 1;

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
      uchar getType() const;

      void onDebugDraw() const;
      

    protected:
      uchar type;

      //collision offset from entity origin
      float offsetX; ///<summary>X-axis offset from entity position</summary>
      float offsetY; ///<summary>Y-axis offset from entity position</summary>
      uint VAO, VBO;
      uint textureID;
      Entity* entity;

      ///<summary>Initialize the VAO</summary>
      void initVAO(float quadW, float quadH);
  };

}
#endif