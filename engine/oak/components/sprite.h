#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <oak/ecs/component.h>
#include <oak/assets/shader.h>
#include <oak/core/types.h>
#include <oak/assets/texture.h>

namespace oak
{
  //Sprite
  class Sprite : public Component
  {
    std::string src;
    uint VBO, VAO;

    public:

      //display size of the sprite
      float w;
      float h;

      //rect of the part of the image to display
      int srcX;
      int srcY;
      int srcW;
      int srcH;

      //resources
      uint textureID;
      uint shaderID;

      Sprite(
        std::string src, 
        int srcX, 
        int srcY, 
        int srcW, 
        int srcH, 
        float displayW, 
        float displayH, 
        std::string shaderName
      );

      Sprite(
        std::string src,
        float displayW,
        float displayH
      );

      ~Sprite();

      //Returns the src file name
      std::string getSrc() const;
      void setSrc(const std::string& s);

      //Returns the VAO
      uint getVAO() const;

    protected:
      void onRender() const override;
    
    private:
      void construct(float xMin, float xMax, float yMin, float yMax);
  };
}

#endif