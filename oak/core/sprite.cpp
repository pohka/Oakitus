#include "sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "store.h"
#include "texture.h"
#include "window.h"

using namespace oak;


Sprite::Sprite(
  std::string src,
  int srcX,
  int srcY,
  int srcW,
  int srcH,
  float displayW,
  float displayH,
  uint shaderID
)
{
  this->srcX = srcX;
  this->srcY = srcY;
  this->srcW = srcW;
  this->srcH = srcH;
  this->w = displayW;
  this->h = displayH;
  
  if (shaderID != NULL)
  {
    this->shaderID = shaderID;
  }
  else 
  {
    shaderID = Resources::defaultShaderID;
  }
  
  Texture *texture = Resources::findTextureBySrc(src);
  this->textureID = texture->getID();
  
  float xMin = ((float)srcX / texture->getWidth());
  float yMin = ((float)srcY / texture->getHeight());
  float xMax = ((float)(srcX+srcW) / texture->getWidth());
  float yMax = ((float)(srcY+srcH) / texture->getHeight());

  float screenH = (float)Window::getHeight();

  float xx = Window::worldToViewportCoords(w);
  float yy = Window::worldToViewportCoords(h);

  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       xMin, yMax, //bottom left
     xx, -yy,       xMax, yMax, //bottom right
     xx,  yy,       xMax, yMin, //top right

     xx,  yy,       xMax, yMin, //top right
    -xx,  yy,       xMin, yMin, //top left
    -xx, -yy,       xMin, yMax, //botom left
  };
  
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);

  glBindVertexArray(this->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  
}

Sprite::~Sprite()
{
  glDeleteVertexArrays(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
}

std::string Sprite::getSrc()
{
  return this->src;
}

unsigned int Sprite::getVAO()
{
  return this->VAO;
}

void Sprite::onDraw()
{
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glBindVertexArray(this->VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Store::camera->getNormalizedPos();
  //float screenH = (float)Window::getHeight();

  glm::vec3 pos(
    Window::worldToViewportCoords(entity->position.x) - camNPos.x,
    Window::worldToViewportCoords(entity->position.y) - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);

  Shader* shader = Resources::findShaderByID(this->shaderID);

  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  
}