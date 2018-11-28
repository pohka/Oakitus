#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "../core/component.h"
#include "../core/shader.h"
#include "../core/types.h"
#include "../core/texture.h"

namespace oak
{
  class Sprite : public Component
  {
    std::string src;
    uint VBO, VAO;

    public:
      float w;
      float h;
      int srcX;
      int srcY;
      int srcW;
      int srcH;
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
        uint shaderID
      );

      Sprite(
        std::string src,
        float displayW,
        float displayH
      );

      ~Sprite();
      std::string getSrc() const;
      uint getVAO() const;
      void onDraw() const override;
    
    private:
      void construct(float xMin, float xMax, float yMin, float yMax);
      Texture* setTextureIDFromSrc(std::string src);
  };
}

#endif