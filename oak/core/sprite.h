#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "component.h"
#include "shader.h"
#include "types.h"

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
    ~Sprite();
    std::string getSrc();
    uint getVAO();
    void onDraw() override;
    

  };
}

#endif