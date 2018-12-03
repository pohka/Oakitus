#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "../core/component.h"
#include "../core/shader.h"
#include "../core/types.h"
#include "../core/texture.h"

namespace oak
{
  ///<summary>Sprite</summary>
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

      ///<summary>Returns the src file name</summary>
      std::string getSrc() const;

      ///<summary>Returns the VAO</summary>
      uint getVAO() const;

    protected:
      void onDraw() const override;
    
    private:
      void construct(float xMin, float xMax, float yMin, float yMax);
  };
}

#endif