#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.h"
#include "Texture.h"
#include "Shader.h"

namespace oak
{
  class Sprite : public Component
  {
    std::string src;
    unsigned int VBO, VAO;
    Texture* texture;

  public:
    Sprite(std::string src, int x, int y, int w, int h, unsigned int shaderID);
    ~Sprite();
    std::string getSrc();
    unsigned int getVAO();
    void onDraw() override;


    int x;
    int y;
    int w;
    int h;
    unsigned int shaderID;

  };
}

#endif