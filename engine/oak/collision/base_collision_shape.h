#ifndef BASE_COLLISION_SHAPE_H
#define BASE_COLLISION_SHAPE_H

#include <oak/core/types.h>
#include <glm/glm.hpp>

///<summary>The base collision shape</summary>
namespace oak
{
  class CollisionRect;
  class CollisionCircle;
  class Entity;



  class BaseCollisionShape
  {

    public:
      friend class Entity;

      BaseCollisionShape();
      ~BaseCollisionShape();
      bool intersects(BaseCollisionShape& shape);

      virtual bool intersectsRect(const CollisionRect& shape) const = 0;
      virtual bool intersectsCircle(const CollisionCircle& shape) const = 0;

      float offsetX() const;
      float offsetY() const;
      glm::vec3 offset() const;
      float originX() const;
      float originY() const;
      glm::vec3 origin() const;

      uchar getType() const;
      bool isTrigger = false;

      void onDebugDraw() const;
      

    protected:
      uchar type;

      //collision offset from entity origin
      float m_offsetX; ///<summary>X-axis offset from entity position</summary>
      float m_offsetY; ///<summary>Y-axis offset from entity position</summary>
      uint VAO, VBO;
      uint textureID;
      Entity* entity;
      

      ///<summary>Initialize the VAO</summary>
      void initVAO(float quadW, float quadH);
  };

}
#endif