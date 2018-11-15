#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "component.h"
#include "texture.h"
#include "shader.h"
#include "types.h"

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