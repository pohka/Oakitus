#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.h"
#include "Texture.h"
#include "Shader.h"
#include "Types.h"

namespace oak
{
  class Sprite : public Component
  {
    std::string src;
    uint VBO, VAO;
    Texture* texture;

  public:
    Sprite(std::string src, int x, int y, int w, int h, uint shaderID);
    ~Sprite();
    std::string getSrc();
    uint getVAO();
    void onDraw() override;


    int x;
    int y;
    int w;
    int h;
    uint shaderID;

  };
}

#endif