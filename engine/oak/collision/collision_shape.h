#pragma once
#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <oak/core/types.h>
#include <glm/glm.hpp>

//The base collision shape
namespace oak
{
  class CollisionRect;
  class CollisionCircle;
  class Entity;



  class CollisionShape
  {

    public:
      friend class Entity;

      //all types of collision shapes
      enum class Type : uchar
      {
        RECT = 0,
        CIRCLE = 1
      };

      CollisionShape();
      ~CollisionShape();
      bool intersects(CollisionShape& shape);

      virtual bool intersectsRect(const CollisionRect& shape) const = 0;
      virtual bool intersectsCircle(const CollisionCircle& shape) const = 0;

      float offsetX() const;
      float offsetY() const;
      glm::vec3 offset() const;
      float originX() const;
      float originY() const;
      glm::vec3 origin() const;
      void setOffset(const float x, const float y);

      Type getType() const;
      bool isTrigger = false;

      void onDebugDraw() const;
      

    protected:
      Type type;

      //collision offset from entity origin
      float m_offsetX; //X-axis offset from entity position
      float m_offsetY; //Y-axis offset from entity position
      uint VAO, VBO;
      uint textureID;
      Entity* entity;
      

      //Initialize the VAO
      void initVAO(float quadW, float quadH);
  };

}
#endif